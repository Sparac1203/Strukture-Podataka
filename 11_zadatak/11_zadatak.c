#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128
#define HASH_SIZE 11

/*DEKLARACIJA STRUKTURE STABLA GRADOVA*/
struct _gradovi_stablo;
typedef struct _gradovi_stablo *Pozicija_sgradovi;
typedef struct _gradovi_stablo
{
    char ime_grada[MAX];
    int broj_stanovnika;
    Pozicija_sgradovi lijevo;
    Pozicija_sgradovi desno;
} S_gradovi;

/*DEKLARACIJA STRUKTURE VEZANE LISTE IMENA DRZAVA*/
struct _drzave_lista;
typedef struct _drzave_lista *Pozicija_ldrzave;
typedef struct _drzave_lista
{
    char ime_drzave[MAX];
    char ime_datoteke[MAX];
    Pozicija_ldrzave next;
    Pozicija_sgradovi root;
} VL_drzave;

/*------------------------------------------DEKLARACIJA OTALIH FUNKCIJA------------------------------------------*/
/*  -za svaki element hash tablice radi poseban head-  */
Pozicija_ldrzave Hash_Drzave_Head(void);
/*  --  */
int Ucitaj_Drzave(Pozicija_ldrzave *hash);
/*  -alocira memoriju za novi element strukture VL_drzave-  */
Pozicija_ldrzave Nova_Drzava_VL(void);
/*  -racuna kljuc za upisivanje u hash tablicu-  */
int Iracunaj_Kljuc_Hash(char *drzava);
/*  -sortirani unos drzava u vezanu listu-  */
Pozicija_ldrzave Sortirani_unos_DrzaveVL(Pozicija_ldrzave Lokacija, Pozicija_ldrzave Nova_Drzava);
/*  -citanje gradova iz datoteke (za stabla)-  */
int Ucitaj_Gradove_S(Pozicija_ldrzave Drzava);
/*  -alocira memoriju za novi element strukture S_gradovi-  */
Pozicija_sgradovi Novi_Grad_S(void);
/*  -soritrani unos gradova u stablo-  */
Pozicija_sgradovi Sortirani_Unos_GradoviS(Pozicija_sgradovi Lokacija, Pozicija_sgradovi Novi_Grad);

/*-------------------------------------------------MAIN FUNKCIJA-------------------------------------------------*/
int main()
{
    /*inicijalizacija hash tablice*/
    Pozicija_ldrzave hash[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hash[i] = Hash_Drzave_Head();
    }

    Ucitaj_Drzave(hash);
    for (int i = 0; i < HASH_SIZE; i++)
    {
        Pozicija_ldrzave drzava = NULL;
        drzava = hash[i]->next;
        while (drzava)
        {
            Ucitaj_Gradove_S(drzava);
            drzava = drzava->next;
        }
    }

    return EXIT_SUCCESS;
}

/*------------------------------------------------OSTALE FUNCKIJE------------------------------------------------*/

Pozicija_ldrzave Hash_Drzave_Head(void)
{
    Pozicija_ldrzave Head = NULL;
    Head = (Pozicija_ldrzave)malloc(sizeof(VL_drzave));
    if (!Head)
    {
        printf("\nNEUSPJESNA ALOKACIJA MEMORIJE ZA HEAD ELEMENT\n");
        return NULL;
    }
    Head->next = NULL;
    Head->root = NULL;

    return Head;
}

int Ucitaj_Drzave(Pozicija_ldrzave *hash)
{

    int kljuc = 0;
    FILE *fp;
    fp = fopen("drzave.txt", "r");
    if (!fp)
    {
        printf("\nNeuspjesno otvaranje datoteke:\t \"drzave.txt\"");
        return EXIT_FAILURE;
    }
    while (!feof(fp))
    {
        Pozicija_ldrzave Nova_drzava = NULL;
        Nova_drzava = Nova_Drzava_VL();
        if (Nova_drzava)
        {
            fscanf(fp, " %s %s", Nova_drzava->ime_drzave, Nova_drzava->ime_datoteke);
            kljuc = Iracunaj_Kljuc_Hash(Nova_drzava->ime_drzave);
            hash[kljuc]->next = Sortirani_unos_DrzaveVL(hash[kljuc]->next, Nova_drzava);
        }
    }

    return EXIT_SUCCESS;
}

Pozicija_ldrzave Nova_Drzava_VL(void)
{
    Pozicija_ldrzave Nova_Drzava = NULL;
    Nova_Drzava = (Pozicija_ldrzave)malloc(sizeof(VL_drzave));
    if (!Nova_Drzava)
    {
        printf("\nNEUSPJESNA ALOKACIJA MEMORIJE ZA NOVU DRZAVU!\n");
        return NULL;
    }
    Nova_Drzava->root = NULL;
    Nova_Drzava->next = NULL;

    return Nova_Drzava;
}

int Iracunaj_Kljuc_Hash(char *drzava)
{
    int kljuc = 0;
    for (int i = 0; i < 5; i++)
    {
        kljuc += (int)drzava[i];
    }
    kljuc = kljuc % 11;
    printf("\n%d", kljuc);

    return kljuc;
}

Pozicija_ldrzave Sortirani_unos_DrzaveVL(Pozicija_ldrzave Lokacija, Pozicija_ldrzave Nova_Drzava)
{
    Pozicija_ldrzave pomocna = NULL;
    pomocna = Lokacija;

    if (!pomocna)
    {
        return Nova_Drzava;
    }

    if (strcmp(pomocna->ime_drzave, Nova_Drzava->ime_drzave) < 0)
    {
        pomocna->next = Sortirani_unos_DrzaveVL(pomocna->next, Nova_Drzava);

        return pomocna;
    }
    else if (strcmp(pomocna->ime_drzave, Nova_Drzava->ime_drzave) > 0)
    {
        Nova_Drzava->next = pomocna;

        return Nova_Drzava;
    }
    else
    {
        free(Nova_Drzava);

        return pomocna;
    }
}

int Ucitaj_Gradove_S(Pozicija_ldrzave Drzava)
{
    FILE *fp;
    fp = fopen(Drzava->ime_datoteke, "r");
    if (!fp)
    {
        printf("\nNeuspjesno otvaranje datoteke:\t \"%s\"", Drzava->ime_datoteke);

        return EXIT_FAILURE;
    }
    while (!feof(fp))
    {
        Pozicija_sgradovi Novi_Grad = NULL;
        Novi_Grad = Novi_Grad_S();
        if (Novi_Grad)
        {
            fscanf(fp, " %s %d", Novi_Grad->ime_grada, &Novi_Grad->broj_stanovnika);
            Drzava->root = Sortirani_Unos_GradoviS(Drzava->root, Novi_Grad);
        }
    }

    return EXIT_SUCCESS;
}

Pozicija_sgradovi Novi_Grad_S(void)
{
    Pozicija_sgradovi Novi_Grad = NULL;
    Novi_Grad = (Pozicija_sgradovi)malloc(sizeof(S_gradovi));
    if (!Novi_Grad)
    {
        printf("\nNEUSPJESNA ALOKACIJA MEMORIJE ZA NOVI GRAD!\n");
        return NULL;
    }
    Novi_Grad->desno = NULL;
    Novi_Grad->lijevo = NULL;

    return Novi_Grad;
}

Pozicija_sgradovi Sortirani_Unos_GradoviS(Pozicija_sgradovi Lokacija, Pozicija_sgradovi Novi_Grad)
{
    if (!Lokacija)
    {
        return Novi_Grad;
    }

    if (Lokacija->broj_stanovnika < Novi_Grad->broj_stanovnika)
    {
        Lokacija->desno = Sortirani_Unos_GradoviS(Lokacija->desno, Novi_Grad);

        return Lokacija;
    }
    else if (Lokacija->broj_stanovnika > Novi_Grad->broj_stanovnika)
    {
        Lokacija->lijevo = Sortirani_Unos_GradoviS(Lokacija->lijevo, Novi_Grad);

        return Lokacija;
    }
    else
    {
        if (strcmp(Lokacija->ime_grada, Novi_Grad->ime_grada) < 0)
        {
            Lokacija->desno = Sortirani_Unos_GradoviS(Lokacija->desno, Novi_Grad);

            return Lokacija;
        }
        else if (strcmp(Lokacija->ime_grada, Novi_Grad->ime_grada) > 0)
        {
            Lokacija->lijevo = Sortirani_Unos_GradoviS(Lokacija->lijevo, Novi_Grad);

            return Lokacija;
        }
        else
        {
            free(Novi_Grad);

            return Lokacija;
        }
    }
}