#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define M 50
#define MAX 1024

struct _Polinom;
typedef struct _Polinom *Pozicija;
typedef struct _Polinom
{
    int koef;
    int eksp;
    Pozicija next;
} polinom;

/*------------------------------------------DEKLARACIJA OTALIH FUNKCIJA------------------------------------------*/
int Ucitaj_Iz_Datoteke(Pozicija p1, Pozicija p2);                     //PRIMA &HEAD1 I &HEAD2, UCITAVA POLINOME IZ DATOTEKE
int Unesi_U_Listu(Pozicija head, char *red);                          //PRIMA HEAD LISTE I NIZ BROJEVA, UPISUJE EKSP I KEOF I POLINOM
int Sortiranje_Liste(Pozicija head);                                  //SORTIRANJE LISTE PREKO BUBBLE SORTA
int Ispisi_Polinom(Pozicija prvi);                                    //ISPISUJE POLINOM
int Zbroji_Polinome(Pozicija head1, Pozicija head2, Pozicija headzb); //ZBRAJA DVA POLINOMA
int Vise_Elemenata_S_Istim_Eksp(Pozicija prvi, Pozicija head);
Pozicija Pronadi_Prethodnog(Pozicija head, int eksp);
int Pomnozi_Polinome(Pozicija head1, Pozicija head2, Pozicija headumn);

/*-------------------------------------------------MAIN FUNKCIJA-------------------------------------------------*/
int main()
{
    polinom head1 = {.koef = 0, .eksp = 0, .next = NULL};
    polinom head2 = {.koef = 0, .eksp = 0, .next = NULL};
    polinom headZbroj = {.koef = 0, .eksp = 0, .next = NULL};
    polinom headUmnozak = {.koef = 0, .eksp = 0, .next = NULL};
    Pozicija p1 = &head1;
    Pozicija p2 = &head2;
    Pozicija p_zbr = &headZbroj;
    Pozicija p_umn = &headUmnozak;
    int a = 0;
    a = Ucitaj_Iz_Datoteke(p1, p2);
    if (a == EXIT_FAILURE)
    {
        return 0;
    }
    Sortiranje_Liste(p1);
    Vise_Elemenata_S_Istim_Eksp(p1->next, p1);
    Sortiranje_Liste(p2);
    Vise_Elemenata_S_Istim_Eksp(p2->next, p2);
    printf("\nPRVI POLINOM...\n");
    Ispisi_Polinom(p1->next);
    printf("\nDRUGI POLINOM...\n");
    Ispisi_Polinom(p2->next);
    Zbroji_Polinome(p1, p2, p_zbr);
    Sortiranje_Liste(p_zbr);
    Vise_Elemenata_S_Istim_Eksp(p_zbr->next, p_zbr);
    printf("\nZROJ DVA POLINOMA...\n");
    Ispisi_Polinom(p_zbr->next);
    Pomnozi_Polinome(p1, p2, p_umn);
    Sortiranje_Liste(p_umn);
    Vise_Elemenata_S_Istim_Eksp(p_umn->next, p_umn);
    printf("\nUMNOZAK DVA POLINOMA...\n");
    Ispisi_Polinom(p_umn->next);

    return EXIT_SUCCESS;
}

/*------------------------------------------------OSTALE FUNCKIJE------------------------------------------------*/
int Ucitaj_Iz_Datoteke(Pozicija p1, Pozicija p2)
{
    FILE *fp = NULL;
    char dat[M] = {0};
    char red[MAX] = {0};
    int status = 0;
    printf("\nIz koje datoteke zelite ucitati polinome?\n");
    scanf(" %s", dat);
    fp = fopen(dat, "r");
    if (fp == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke %s !\n", dat);
        return EXIT_FAILURE;
    }
    fgets(red, MAX, fp); //UPISIVANJE U PRVU LISTU
    status = Unesi_U_Listu(p1, red);
    if (status != EXIT_SUCCESS)
    {
        printf("\nGRESKA U UPISIVANJU PRVOG POLINOMA U LISTU\n\n");
        return -5;
    }
    fgets(red, MAX, fp); //UPISIVANJE U DRUGU LISTU
    status = Unesi_U_Listu(p2, red);
    if (status != EXIT_SUCCESS)
    {
        printf("\nGRESKA U UPISIVANJU DRUGOG POLINOMA U LISTU\n\n");
        return -5;
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int Unesi_U_Listu(Pozicija head, char *red)
{
    int koef_pom = 0;
    int ekspo_pom = 0;
    int bajtovi = 0;
    int status = 2;
    char *pomoc = red;
    Pozicija Novi_Element = NULL;
    while (strlen(pomoc) > 0)
    {
        status = sscanf(pomoc, " %d %d %n", &koef_pom, &ekspo_pom, &bajtovi);
        if (status != 2)
        {
            return EXIT_FAILURE;
        }
        Novi_Element = (Pozicija)malloc(sizeof(polinom));
        if (!Novi_Element)
        {
            perror("\nAlokacija memorije neuspjesna!\n");
            return EXIT_FAILURE;
        }
        Novi_Element->eksp = ekspo_pom;
        Novi_Element->koef = koef_pom;
        Novi_Element->next = head->next;
        head->next = Novi_Element;
        pomoc += bajtovi;
    }

    return EXIT_SUCCESS;
}

int Sortiranje_Liste(Pozicija head)
{
    Pozicija i = NULL, j = NULL, prosli_j = NULL, pomoc = NULL, kraj = NULL;
    i = head;
    while (i->next != kraj)
    {
        prosli_j = i;
        j = i->next;
        while (j->next != kraj)
        {
            if (j->eksp > j->next->eksp)
            {
                pomoc = j->next;
                prosli_j->next = pomoc;
                j->next = pomoc->next;
                pomoc->next = j;
                j = pomoc;
            }
            prosli_j = j;
            j = j->next;
        }
        kraj = j;
    }

    return EXIT_SUCCESS;
}

int Ispisi_Polinom(Pozicija prvi)
{
    Pozicija pomoc = NULL;
    pomoc = prvi;
    int brojac = 0;
    do
    {
        if (brojac != 0)
        {
            if (pomoc->koef >= 0)
            {
                printf("  +  ");
            }
            else
            {
                printf("  -  ");
            }
        }
        if (pomoc->eksp >= 0)
        {
            printf("%dx^%d", abs(pomoc->koef), pomoc->eksp);
        }
        else
        {
            printf("%dx^(%d)", abs(pomoc->koef), pomoc->eksp);
        }
        pomoc = pomoc->next;
        brojac++;
    } while (pomoc != NULL);
    printf("\n");

    return EXIT_SUCCESS;
}
int Zbroji_Polinome(Pozicija head1, Pozicija head2, Pozicija headzb)
{
    Pozicija pom1 = NULL;
    Pozicija pom2 = NULL;
    Pozicija Novi_Element = NULL;
    for (pom1 = head1->next; pom1 != NULL; pom1 = pom1->next)
    {
        Novi_Element = (Pozicija)malloc(sizeof(polinom));
        if (!Novi_Element)
        {
            perror("\nAlokacija memorije neuspjesna!\n");
            return EXIT_FAILURE;
        }
        Novi_Element->eksp = pom1->eksp;
        Novi_Element->koef = pom1->koef;
        Novi_Element->next = headzb->next;
        headzb->next = Novi_Element;
    }
    for (pom2 = head2->next; pom2 != NULL; pom2 = pom2->next)
    {
        Novi_Element = (Pozicija)malloc(sizeof(polinom));
        if (!Novi_Element)
        {
            perror("\nAlokacija memorije neuspjesna!\n");
            return EXIT_FAILURE;
        }
        Novi_Element->eksp = pom2->eksp;
        Novi_Element->koef = pom2->koef;
        Novi_Element->next = headzb->next;
        headzb->next = Novi_Element;
    }

    return EXIT_SUCCESS;
}

int Vise_Elemenata_S_Istim_Eksp(Pozicija prvi, Pozicija head)
{
    Pozicija pomoc = NULL;
    Pozicija Prethodni = NULL;
    Pozicija Novi_Element = NULL;
    for (pomoc = prvi; pomoc->next != NULL; pomoc = pomoc->next)
    {
        if (pomoc->eksp == pomoc->next->eksp)
        {
            Novi_Element = (Pozicija)malloc(sizeof(polinom));
            if (!Novi_Element)
            {
                perror("\nAlokacija memorije neuspjesna!\n");
                return EXIT_FAILURE;
            }
            Prethodni = Pronadi_Prethodnog(head, pomoc->eksp);
            Novi_Element->eksp = pomoc->eksp;
            Novi_Element->koef = pomoc->koef + pomoc->next->koef;
            Novi_Element->next = pomoc->next->next;
            Prethodni->next = Novi_Element;
        }
    }

    return EXIT_SUCCESS;
}

Pozicija Pronadi_Prethodnog(Pozicija head, int eksp)
{
    Pozicija prosli = NULL, trenutni = NULL;
    prosli = head;
    trenutni = prosli->next;
    while (trenutni != NULL && trenutni->eksp != eksp)
    {
        prosli = trenutni;
        trenutni = prosli->next;
    }
    if (trenutni == NULL)
    {
        return NULL;
    }

    return prosli;
}

int Pomnozi_Polinome(Pozicija head1, Pozicija head2, Pozicija headumn)
{
    Pozicija pom1 = NULL;
    Pozicija pom2 = NULL;
    Pozicija Novi_Element = NULL;
    for (pom1 = head1->next; pom1 != NULL; pom1 = pom1->next)
    {
        for (pom2 = head2->next; pom2 != NULL; pom2 = pom2->next)
        {
            Novi_Element = (Pozicija)malloc(sizeof(polinom));
            if (!Novi_Element)
            {
                perror("\nAlokacija memorije neuspjesna!\n");
                return EXIT_FAILURE;
            }
            Novi_Element->eksp = pom1->eksp + pom2->eksp;
            Novi_Element->koef = pom1->koef * pom2->koef;
            Novi_Element->next = headumn->next;
            headumn->next = Novi_Element;
        }
    }

    return EXIT_SUCCESS;
}