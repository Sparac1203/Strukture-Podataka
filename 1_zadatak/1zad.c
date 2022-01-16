#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX 1024
#define M 64

typedef struct _Stud
{
    char ime[M];
    char prezime[M];
    double bodovi;
} student;

//Deklariranje ostalih fja---------------------------------------------------
int BrStud(char *);                      //uzima string s imenom datoteke i racuna broj studenata
double relativni_bodovi(double, double); //uzima bodove, maksimalni postignuti bodovi i racuna relativne bodove
//Main fja-------------------------------------------------------------------
int main()
{

    int br_Stud = 0, i;
    double max_bodovi = 0;
    student *s = NULL;
    char dat[M] = {0};
    FILE *fp = NULL;
    char IME[M] = {"IME"},
         PREZIME[M] = {"PREZIME"},
         Bd1[M] = {"BODOVI(apsolutno)"},
         Bd2[M] = {"BODOVI(relativno)"};

    printf("\nUnesite naziv datoteke koju zelite procitati:\t");
    scanf(" %s", &dat);
    br_Stud = BrStud(dat);
    if (br_Stud < 0)
    {
        return -1;
    }
    printf("\nUkupan broj studenata je %d\n\n", br_Stud);
    fp = fopen(dat, "r");
    s = (student *)malloc(br_Stud * sizeof(student));
    if (!s)
    {
        printf("\nALOKACIJA MEMORIJE NIJE USPJELA\n");
        return -2;
    }
    for (i = 0; i < br_Stud; i++) //pridjeljuje podatke svakom studentu
    {
        fscanf(fp, "%s %s %lf", s[i].ime, s[i].prezime, &s[i].bodovi);
    }
    for (i = 0; i < br_Stud; i++) //pronalazi maksimalan broj bodova
    {
        if (s[i].bodovi >= max_bodovi)
        {
            max_bodovi = s[i].bodovi;
        }
    }

    printf("%-25s %-25s %-25s %-25s\n\n", IME, PREZIME, Bd1, Bd2);
    for (i = 0; i < br_Stud; i++)
    {
        double rel_bod = 0.0;
        rel_bod = relativni_bodovi(s[i].bodovi, max_bodovi);
        printf("\n%-25s %-25s %-25.2lf %-25.2lf ", s[i].ime, s[i].prezime, s[i].bodovi, rel_bod);
    }
    fclose(fp);
    printf("\n\n");
    return 0;
}
//Ostale fje-----------------------------------------------------------------
int BrStud(char *dat)
{
    int br = 0;
    char red[MAX] = {0}, pomoc[MAX];
    FILE *fp = NULL;
    fp = fopen(dat, "r");
    if (fp == NULL)
    {
        printf("\nNIJE USPJELO OTVARANJE DATOTEKE -> %s\n", dat);
        return -1;
    }
    while (!feof(fp))
    {
        fgets(red, MAX, fp);
        if (*red == '\n') //zanemaruje mogucih praznih x redaka do kraja datoteke
        {
            continue;
        }
        else
        {
            br++;
        }
    }
    fclose(fp);
    return br;
}
double relativni_bodovi(double x, double y)
{
    double bod = 0.0;
    bod = (x / y) * 100;
    return bod;
}