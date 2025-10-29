#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person {
    char name[50];
    char surname[50];
    int birthYear;
    struct _person *next;
} Person;

typedef Person* Position;

// new person
Position createPerson(const char *name, const char *surname, int birthYear) {
    Position newPerson = (Position)malloc(sizeof(Person));
    if (!newPerson) {
        printf("memory allocation error\n");
        return NULL;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

// new person na početak
void addAtBeginning(Position head, const char *name, const char *surname, int birthYear) {
    Position newPerson = createPerson(name, surname, birthYear);
    if (!newPerson) return;

    newPerson->next = head->next;
    head->next = newPerson;
}

// new person na kraj
void addAtEnd(Position head, const char *name, const char *surname, int birthYear) {
    Position newPerson = createPerson(name, surname, birthYear);
    if (!newPerson) return;

    Position current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newPerson;
}

// Printanje liste
void printList(Position head) {
    Position current = head->next; 
    printf("\nList of people:\n");
    while (current != NULL) {
        printf("%s %s (%d)\n", current->name, current->surname, current->birthYear);
        current = current->next;
    }
}

// trazenje po prezimenu
Position findBySurname(Position head, const char *surname) {
    Position current = head->next;
    while (current != NULL && strcmp(current->surname, surname) != 0) {
        current = current->next;
    }
    return current; // NULL ako ne nađe
}

// brisanje po prezimenu
int deleteBySurname(Position head, const char *surname) {
    Position prev = head;
    Position current = head->next;

    while (current != NULL && strcmp(current->surname, surname) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Person not found\n");
        return -1;
    }

    prev->next = current->next;
    free(current);
    return 0;
}


//3. ZADATAK OVDJE

int addAfter(Position head, const char *targetSurname, const char *name, const char *surname, int birthYear) {
    Position target = findBySurname(head, targetSurname);
    if (!target) {
        printf("person with surnaem '%s' not found\n", targetSurname);
        return -1;
    }

    Position newPerson = createPerson(name, surname, birthYear);
    if (!newPerson) return -1;

    newPerson->next = target->next;
    target->next = newPerson;
    return 0;
}

// B. dodavanje osobe prije prezimena
int addBefore(Position head, const char *targetSurname, const char *name, const char *surname, int birthYear) {
    Position prev = head;
    Position current = head->next;

    while (current != NULL && strcmp(current->surname, targetSurname) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("person with surnaem '%s' not found\n", targetSurname);
        return -1;
    }

    Position newPerson = createPerson(name, surname, birthYear);
    if (!newPerson) return -1;

    newPerson->next = current;
    prev->next = newPerson;
    return 0;
}

// C. sortiranje po prezimenu abecedno
void sortBySurname(Position head) {
    if (head->next == NULL || head->next->next == NULL)
        return; 

    Position end = NULL;
    while (head->next != end) {
        Position prev = head;
        Position curr = head->next;

        while (curr->next != end) {
            if (strcmp(curr->surname, curr->next->surname) > 0) {
               
                Position temp = curr->next;
                curr->next = temp->next;
                temp->next = curr;
                prev->next = temp;

                curr = temp; 
            }
            prev = curr;
            curr = curr->next;
        }
        end = curr;
    }
}

// D. otvaranje liste za pisanje
int writeToFile(Position head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("error\n");
        return -1;
    }

    Position current = head->next;
    while (current != NULL) {
        fprintf(fp, "%s %s %d\n", current->name, current->surname, current->birthYear);
        current = current->next;
    }

    fclose(fp);
    printf("list written to '%s'\n", filename);
    return 0;
}

// E. citanje liste
int readFromFile(Position head, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("error\n");
        return -1;
    }

    char name[50], surname[50];
    int birthYear;

    while (fscanf(fp, "%s %s %d", name, surname, &birthYear) == 3)
        addAtEnd(head, name, surname, birthYear);

    fclose(fp);
    printf("list read from '%s'\n", filename);
    return 0;
}

//mejn

int main() {
    Person head = { .name = "", .surname = "", .birthYear = 0, .next = NULL };

    // pocetna lista
    addAtBeginning(&head, "Pero", "Peric", 1980);
    addAtEnd(&head, "Djuro", "Djuric", 1975);
    addAtEnd(&head, "Mile", "Kitic", 1952);
    printList(&head);

    // dodavanje after i b4
    addAfter(&head, "Djuric", "Andrija", "Mohorovcic", 1990);
    addBefore(&head, "Peric", "Vicko", "Svetac", 2000);
    printList(&head);

    // sortiranje po prezimenu
    sortBySurname(&head);
    printf("\nsorting by surname:\n");
    printList(&head);

    // citanje datoteke
    writeToFile(&head, "people.txt");

    // pravljenje nove i dodavanje head
    Person newHead = { .name = "", .surname = "", .birthYear = 0, .next = NULL };
    readFromFile(&newHead, "people.txt");

    printf("\nlist loaded from file:\n");
    printList(&newHead);


    return 0;
}
