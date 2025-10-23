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
        printf("Memory allocation error!\n");
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
        printf("Person not found!\n");
        return -1;
    }

    prev->next = current->next;
    free(current);
    return 0;
}

// glavna funkc
int main() {
    Person head = { .name = "", .surname = "", .birthYear = 0, .next = NULL };

    // dodavanje ljudi 
    addAtBeginning(&head, "Pero", "Perić", 1980);
    addAtEnd(&head, "Đuro", "Đurić", 1975);
    addAtEnd(&head, "Mile", "Kitić", 1952);

    printList(&head);

    printf("\nSearching for 'Đurić'...\n");
    Position found = findBySurname(&head, "Đurić");
    if (found)
        printf("Found: %s %s (%d)\n", found->name, found->surname, found->birthYear);
    else
        printf("Person not found.\n");

    printf("\nDeleting 'Perić'...\n");
    deleteBySurname(&head, "Perić");

    printList(&head);

    return 0;
}
