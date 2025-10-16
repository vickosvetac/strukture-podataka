#include <stdio.h>
#include <stdlib.h>
#define MAX_IME 50
#define MAX_PREZIME 50
typedef struct student {
    char ime[MAX_IME];
    char prezime[MAX_PREZIME];
    int bodovi;
} _stud;


int broj_redova(char *dat) {
    FILE *fp = fopen(dat, "r");
    if (fp == NULL) return 0;
    int brojac = 0;
    char buffer[200];
    while (fgets(buffer, sizeof(buffer),fp) != NULL) {
        brojac++;
    }
    fclose(fp);
    return brojac;
}


int main() {
    char dat[] = "studenti.txt";
    int n = broj_redova(dat);

    //dinamicka alokacija
    _stud *studenti = (_stud*)malloc(n*sizeof(_stud));
    if (studenti == NULL) {
        printf("Greska!");
        return 1;
    }

    //otvaranje dat
    FILE *fp = fopen(dat, "r");
    if (fp == NULL) {
        printf("ne moze se otvorit datoteka");
        free(studenti);
        return 1;
    }

    //podaci

    int i = 0;
    int max_bodova = 0;
    while(fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi)== 3) {
        if (studenti[i].bodovi > max_bodova)
        max_bodova = studenti[i].bodovi;
        i++;
    }
    fclose(fp);
    //rezultat
    printf("Ime\tPrezime\tBodovi\tRelativno %%\n");
    for (i = 0;i < n; i++) {
        double relativno = (double)studenti[i].bodovi / max_bodova * 100;
        printf("%s\t%s\t%d\t%.2f%%\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativno);
    }
free(studenti);
return 0;
}