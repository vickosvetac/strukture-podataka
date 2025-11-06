#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//struct
typedef struct {
    int coef;
    int exp;
} Term;

//prototipi funkc
int findExp(Term p[], int n, int exp);
int readPolynomial(FILE *f, Term p[], int maxTerms);
int addPoly(Term p1[], int n1, Term p2[], int n2, Term result[], int maxTerms);
int multiplyPoly(Term p1[], int n1, Term p2[], int n2, Term result[], int maxTerms);
int printPoly(Term p[], int n);

//

// trazenje exp polinoma
int findExp(Term p[], int n, int exp) {
    int i;
    for (i = 0; i < n; i++) {
        if (p[i].exp == exp)
            return i;
    }
    return -1;
}

// citanje polinoma iz filea
int readPolynomial(FILE *f, Term p[], int maxTerms) {
    int n = 0;
    while (n < maxTerms && fscanf(f, "%d%d", &p[n].coef, &p[n].exp) == 2) {
        n++;
        if (fgetc(f) == '\n' || feof(f))
            break; //iduci polinom
    }
    return n;
}

// dodavanje 2 polinoma
int addPoly(Term p1[], int n1, Term p2[], int n2, Term result[], int maxTerms) {
    int n = 0;
    int i;
    for (i = 0; i < n1 && n < maxTerms; i++) {
        result[n] = p1[i];
        n++;
    }

    for (i = 0; i < n2; i++) {
        int pos = findExp(result, n, p2[i].exp);
        if (pos == -1 && n < maxTerms) {
            result[n] = p2[i];
            n++;
        } else if (pos != -1) {
            result[pos].coef += p2[i].coef;
        }
    }
    return n;
}

// mnozenje 2 polinoma
int multiplyPoly(Term p1[], int n1, Term p2[], int n2, Term result[], int maxTerms) {
    int n = 0;
    int i, j;
    for (i = 0; i < n1; i++) {
        for (j = 0; j < n2; j++) {
            int coef = p1[i].coef * p2[j].coef;
            int exp = p1[i].exp + p2[j].exp;
            int pos = findExp(result, n, exp);

            if (pos == -1 && n < maxTerms) {
                result[n].coef = coef;
                result[n].exp = exp;
                n++;
            } else if (pos != -1) {
                result[pos].coef += coef;
            }
        }
    }
    return n;
}

// print
int printPoly(Term p[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (p[i].coef == 0) continue;
        if (i > 0 && p[i].coef > 0) printf("+");
        if (p[i].exp == 0)
            printf("%d", p[i].coef);
        else if (p[i].exp == 1)
            printf("%dx", p[i].coef);
        else
            printf("%dx^%d", p[i].coef, p[i].exp);
    }
    printf("\n");
    return 0;
}

//glavna funkc
int main() {
    FILE *f;
    Term p1[MAX];
    Term p2[MAX];
    Term sum[MAX];
    Term product[MAX];
    int n1, n2, ns, np;

    f = fopen("polinomi.txt", "r");
    if (f == NULL) {
        printf("error\n");
        return 1;
    }

    n1 = readPolynomial(f, p1, MAX);
    n2 = readPolynomial(f, p2, MAX);
    fclose(f);

    printf("First polynomial: ");
    printPoly(p1, n1);

    printf("Second polynomial: ");
    printPoly(p2, n2);

    ns = addPoly(p1, n1, p2, n2, sum, MAX);
    np = multiplyPoly(p1, n1, p2, n2, product, MAX);

    printf("\nSum: ");
    printPoly(sum, ns);

    printf("Product: ");
    printPoly(product, np);

    return 0;
}
