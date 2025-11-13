#include <stdio.h>
#include <stdlib.h>

typedef struct _poly* Position;

typedef struct _poly {
    int coef;
    int pow;
    Position next;
} Poly;

//prototipi funkc
Position createEl(int coef, int pow);
int insertSorted(Position head, int coef, int pow);
int readFile(Position head, const char* filename);
Position addPoly(Position firstP, Position secondP);
Position multiplyPoly(Position firstP, Position secondP);
int printPoly(Position head);
int freeList(Position head);

//main
int main() {
    Poly head1 = { .coef = 0, .pow = 0, .next = NULL };
    Poly head2 = { .coef = 0, .pow = 0, .next = NULL };
    Poly headSum = { .coef = 0, .pow = 0, .next = NULL };
    Poly headProduct = { .coef = 0, .pow = 0, .next = NULL };

    //otvaranje i citanje
    readFile(&head1, "poly1.txt");
    readFile(&head2, "poly2.txt");

    printf("First polynomial: ");
    printPoly(&head1);
    printf("Second polynomial: ");
    printPoly(&head2);

    //zbrajanje mnozenje
    headSum.next = addPoly(&head1, &head2);
    headProduct.next = multiplyPoly(&head1, &head2);

    printf("\nSum: ");
    printPoly(&headSum);
    printf("Product: ");
    printPoly(&headProduct);

    //freeanje memorije
    freeList(&head1);
    freeList(&head2);
    freeList(&headSum);
    freeList(&headProduct);

    return 0;
}


//alociranje novog nodea
Position createEl(int coef, int pow) {
    Position newEl = (Position)malloc(sizeof(Poly));
    if (newEl == NULL) return NULL;
    newEl->coef = coef;
    newEl->pow = pow;
    newEl->next = NULL;
    return newEl;
}

//insert s vise na nizu vri.
int insertSorted(Position head, int coef, int pow) {
    Position previous = head;
    Position p = previous->next;
    Position newEl = NULL;

    newEl = createEl(coef, pow);
    if (newEl == NULL) return -1;

    //praznjenje liste
    if (p == NULL) {
        previous->next = newEl;
        return 0;
    }

 
    while (p != NULL && p->pow > pow) {
        previous = p;
        p = p->next;
    }

  
    if (p != NULL && p->pow == pow) {
        p->coef += coef;
        free(newEl);
    }
    else {
        newEl->next = previous->next;
        previous->next = newEl;
    }

    return 0;
}

//citanje polinoma iz filea
int readFile(Position head, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening file %s\n", filename);
        return -1;
    }

    int coef = 0, pow = 0;
    while (fscanf(f, "%d %d", &coef, &pow) == 2) {
        insertSorted(head, coef, pow);
    }

    fclose(f);
    return 0;
}

//dodavanje 2 polioma
Position addPoly(Position firstP, Position secondP) {
    Poly head = { .coef = 0, .pow = 0, .next = NULL };
    Position p1 = firstP->next;
    Position p2 = secondP->next;

    while (p1 != NULL) {
        insertSorted(&head, p1->coef, p1->pow);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        insertSorted(&head, p2->coef, p2->pow);
        p2 = p2->next;
    }
    return head.next;
}

//mnozenje 2 polinoma
Position multiplyPoly(Position firstP, Position secondP) {
    Poly head = { .coef = 0, .pow = 0, .next = NULL };
    Position p1 = firstP->next;
    Position p2 = NULL;

    while (p1 != NULL) {
        p2 = secondP->next;
        while (p2 != NULL) {
            insertSorted(&head, p1->coef * p2->coef, p1->pow + p2->pow);
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return head.next;
}

// Printanje polinoma
int printPoly(Position head) {
    Position p = head->next;
    if (p == NULL) {
        printf("0\n");
        return 0;
    }

    while (p != NULL) {
        if (p != head->next && p->coef >= 0) printf("+");
        printf("%dx^%d", p->coef, p->pow);
        p = p->next;
    }
    printf("\n");
    return 0;
}

//freeanje liste
int freeList(Position head) {
    Position temp = NULL;
    Position p = head->next;
    while (p != NULL) {
        temp = p;
        p = p->next;
        temp->next = NULL;
        free(temp);
    }
    head->next = NULL;
    return 0;
}
