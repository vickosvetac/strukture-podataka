#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 11

//strukture

typedef struct city* TreePos;
typedef struct country* Position;

struct city {
    char name[50];
    int population;
    TreePos left;
    TreePos right;
};

struct country {
    char name[50];
    Position next;
    TreePos root;
};

//funkcije

int hashFunction(char* name);

TreePos insertCity(TreePos root, char* name, int pop);
int printCities(TreePos root);
int searchCities(TreePos root, int min);
int freeCityTree(TreePos root);

Position createCountry(char* name);
int insertCountrySorted(Position head, Position newCountry);
int loadCities(Position country, char* filename);
int freeCountries(Position head);

//hash

int hashFunction(char* name) {
    int sum = 0;
    for (int i = 0; i < 5 && name[i] != '\0'; i++)
        sum += (int)name[i];

    return sum % TABLE_SIZE;
}

//stablo gradova

TreePos insertCity(TreePos root, char* name, int pop) {
    if (root == NULL) {
        TreePos new = malloc(sizeof(struct city));
        if (!new) return NULL;

        strcpy(new->name, name);
        new->population = pop;
        new->left = new->right = NULL;
        return new;
    }

    if (pop < root->population ||
        (pop == root->population && strcmp(name, root->name) < 0))
        root->left = insertCity(root->left, name, pop);
    else
        root->right = insertCity(root->right, name, pop);

    return root;
}

int printCities(TreePos root) {
    if (!root) return 0;

    printCities(root->left);
    printf("   %s (%d)\n", root->name, root->population);
    printCities(root->right);

    return 0;
}

int searchCities(TreePos root, int min) {
    if (!root) return 0;

    searchCities(root->right, min);
    if (root->population > min)
        printf("   %s (%d)\n", root->name, root->population);
    searchCities(root->left, min);

    return 0;
}

int freeCityTree(TreePos root) {
    if (!root) return 0;

    freeCityTree(root->left);
    freeCityTree(root->right);
    free(root);

    return 0;
}

//drzave

Position createCountry(char* name) {
    Position new = malloc(sizeof(struct country));
    if (!new) return NULL;

    strcpy(new->name, name);
    new->root = NULL;
    new->next = NULL;

    return new;
}

int insertCountrySorted(Position head, Position newCountry) {
    Position p = head;

    while (p->next && strcmp(p->next->name, newCountry->name) < 0)
        p = p->next;

    newCountry->next = p->next;
    p->next = newCountry;

    return 0;
}

int loadCities(Position country, char* filename) {
    FILE* f = fopen(filename, "r");
    char city[50];
    int pop;

    if (!f) {
        printf("Ne mogu otvoriti %s\n", filename);
        return -1;
    }

    while (fscanf(f, " %[^,],%d", city, &pop) == 2)
        country->root = insertCity(country->root, city, pop);

    fclose(f);
    return 0;
}

int freeCountries(Position head) {
    Position temp;

    while (head->next) {
        temp = head->next;
        head->next = temp->next;

        freeCityTree(temp->root);
        free(temp);
    }

    return 0;
}


int main() {
    FILE* f = fopen("drzave.txt", "r");
    char countryName[50], fileName[50];

    Position hashTable[TABLE_SIZE];

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = malloc(sizeof(struct country));
        hashTable[i]->next = NULL;
        hashTable[i]->root = NULL;
        strcpy(hashTable[i]->name, "");
    }

    while (fscanf(f, "%s %s", countryName, fileName) == 2) {
        int key = hashFunction(countryName);

        Position new = createCountry(countryName);
        loadCities(new, fileName);
        insertCountrySorted(hashTable[key], new);
    }
    fclose(f);

    //ispis
    for (int i = 0; i < TABLE_SIZE; i++) {
        Position p = hashTable[i]->next;
        while (p) {
            printf("\nDrzava: %s (hash %d)\n", p->name, i);
            printCities(p->root);
            p = p->next;
        }
    }

    //search
    char searchCountry[50];
    int minPop;

    printf("\nUnesi drzavu: ");
    scanf("%s", searchCountry);
    printf("Minimalni broj stanovnika: ");
    scanf("%d", &minPop);

    int key = hashFunction(searchCountry);
    Position p = hashTable[key]->next;

    while (p && strcmp(p->name, searchCountry))
        p = p->next;

    if (p)
        searchCities(p->root, minPop);
    else
        printf("Drzava ne postoji.\n");

    //free
    for (int i = 0; i < TABLE_SIZE; i++) {
        freeCountries(hashTable[i]);
        free(hashTable[i]);
    }

    return 0;
}

