#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//grad u stablo
TreePos insertCity(TreePos root, char* name, int pop) {
    if (root == NULL) {
        TreePos new = malloc(sizeof(struct city));
        strcpy(new->name, name);
        new->population = pop;
        new->left = new->right = NULL;
        return new;
    }

    if (pop < root->population || 
        (pop == root->population && strcmp(name, root->name) < 0)) {
        root->left = insertCity(root->left, name, pop);
    } else {
        root->right = insertCity(root->right, name, pop);
    }

    return root;
}

//ispis gradova
int printCities(TreePos root) {
    if (root == NULL) return 0;
    printCities(root->left);
    printf("   %s (%d)\n", root->name, root->population);
    printCities(root->right);
    return 0;
}

//min stanovnici
int searchCities(TreePos root, int min) {
    if (root == NULL) return 0;
    searchCities(root->right, min);
    if (root->population > min) {
        printf("   %s (%d)\n", root->name, root->population);
    }
    searchCities(root->left, min);
    return 0;
}

//novi cvor
Position createCountry(char* name) {
    Position new = malloc(sizeof(struct country));
    strcpy(new->name, name);
    new->root = NULL;
    new->next = NULL;
    return new;
}

//drzava u vezanu listu
int insertCountrySorted(Position head, Position new) {
    Position p = head;
    while (p->next != NULL && strcmp(p->next->name, new->name) < 0) {
        p = p->next;
    }

    new->next = p->next;
    p->next = new;
    return 0;
}

//ucitavanje gradova iz datoteke
int loadCities(Position country, char* filename) {
    FILE* f = fopen(filename, "r");
    char city[50];
    int pop;

    if (!f) {
        printf("Ne mogu otvoriti %s\n", filename);
        return -1;
    }

    while (fscanf(f, " %[^,],%d", city, &pop) == 2) {
        country->root = insertCity(country->root, city, pop);
    }

    fclose(f);
    return 0;
}

// Glavni program
int main() {
    FILE* f = fopen("drzave.txt", "r");
    char countryName[50], fileName[50];

  
    struct country head = {.name = "", .next = NULL, .root = NULL};

    //gradovi i drzave
    while (fscanf(f, "%s %s", countryName, fileName) == 2) {
        Position new = createCountry(countryName);
        loadCities(new, fileName);
        insertCountrySorted(&head, new);
    }
    fclose(f);

    //ispis
    Position p = head.next;
    while (p != NULL) {
        printf("\nDrzava: %s\n", p->name);
        printCities(p->root);
        p = p->next;
    }

    //pretraga prema min stanovnika
    char searchCountry[50];
    int minPop;

    printf("\nUnesi drzavu: ");
    scanf("%s", searchCountry);
    printf("Minimalni broj stanovnika: ");
    scanf("%d", &minPop);

    //nalazenje države i ispis gradova s vise stanovnika
    p = head.next;
    while (p && strcmp(p->name, searchCountry) != 0) {
        p = p->next;
    }

    if (p)
        searchCities(p->root, minPop);
    else
        printf("Drzava ne postoji.\n");

    return 0;
}
