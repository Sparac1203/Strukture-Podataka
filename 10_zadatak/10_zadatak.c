#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128

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

/*DEKLARACIJA STRUKTURE VEZANE LISTE IMENA GRADOVA*/
struct _gradovi_lista;
typedef struct _gradovi_lista *Pozicija_VLgradovi;
typedef struct _gradovi_lista
{
    char ime_grada[MAX];
    int broj_stanovnika;
    Pozicija_VLgradovi next;
} VL_gradovi;

/*DEKLARACIJA STRUKTURE STABLA DRZAVA*/
struct _drzave_stablo;
typedef struct _drzave_stablo *Pozicija_sdrzave;
typedef struct _drzave_stablo
{
    char ime_drzave[MAX];
    char ime_datoteke[MAX];
    Pozicija_sdrzave lijevo;
    Pozicija_sdrzave desno;
    Pozicija_VLgradovi head;
} S_drzave;

/*------------------------------------------DEKLARACIJA OTALIH FUNKCIJA------------------------------------------*/

/*  -ispisuje moguce opcije rada s drzavama i gradovima-  */
int Ispis_Opcija(char *odabir_opcije);

//a
/*  -citanje drzava iz datoteke (za vezane liste)-  */
int Ucitaj_DrzaveVL(Pozicija_ldrzave head);
/*  -alocira memoriju za novi element strukture VL_drzave-  */
Pozicija_ldrzave Nova_Drzava_VL(void);
/*  -sortirani unos drzava u vezanu listu-  */
Pozicija_ldrzave Sortirani_unos_DrzaveVL(Pozicija_ldrzave Lokacija, Pozicija_ldrzave Nova_Drzava);
/*  -citanje gradova iz datoteke (za stabla)-  */
int Ucitaj_Gradove_S(Pozicija_ldrzave Drzava);
/*  -alocira memoriju za novi element strukture S_gradovi-  */
Pozicija_sgradovi Novi_Grad_S(void);
/*  -soritrani unos gradova u stablo-  */
Pozicija_sgradovi Sortirani_Unos_GradoviS(Pozicija_sgradovi Lokacija, Pozicija_sgradovi Novi_Grad);
/*  -ispisuje vezanu listu drzava-  */
int Ispisi_Drzave_VL(Pozicija_ldrzave head);
/*  -u inorder poretku ispisuje gradove pojedine drzave-  */
int Ispisi_Gradove_S(Pozicija_sgradovi root);
/*  -pretrazivanje gradova po drzavama po broju stanovnika-  */
int Pretraga_a(Pozicija_ldrzave head);
/*  -Trazi unesenu drzavu u vezanoj listi-  */
int Pronadi_Drzavu_VL(Pozicija_ldrzave head, char ime_drzave[MAX]);
/*  -pronalazi sve gradove u zadanom randu broja stanovnika-  */
int Pronadi_Gradove_S(Pozicija_ldrzave Drzava);
/*  -ispisuje sve gradove s brojem stanovnika vecim od unesenog broja-  */
int Ispis_Gradova_S_min(Pozicija_sgradovi _Lokacija, int min_broj_stan);

//b
/*  -citanje drzava iz datoteke (za stablo)-  */
Pozicija_sdrzave Ucitaj_DrzaveS(Pozicija_sdrzave root);
/*  -alocira memoriju za novi element strukture S_drzave-  */
Pozicija_sdrzave Nova_Drzava_S(void);
/*  -alocira memoriju za novi element strukture VL_gradovi-  */
Pozicija_VLgradovi Novi_Grad_VL(void);
/*  -sortirani unos drzava u stablo-  */
Pozicija_sdrzave Sortirani_unos_DrzaveS(Pozicija_sdrzave Lokacija, Pozicija_sdrzave Nova_Drzava);
/*  -Prolazi kroz sve elemente stabla i svakoj drzavi pridodjeli vezanu listu gradova-  */
int Inorder_Drzave(Pozicija_sdrzave root);
/*  -citanje gradova iz datoteke (za vezane liste)-  */
Pozicija_sdrzave Ucitaj_Gradove_VL(Pozicija_sdrzave Drzava);
/*  -soritrani unos gradova u vezanu listu-  */
Pozicija_VLgradovi Sortirani_Unos_GradoviVL(Pozicija_VLgradovi Lokacija, Pozicija_VLgradovi Novi_Grad);
/*  -u inorder poretku ispisuje sve zapisane drzave-  */
int Ispisi_Drzave_S(Pozicija_sdrzave root);
/*  -ispisuje vezanu listu gradova-  */
int Ispisi_Gradove_VL(Pozicija_VLgradovi head);
/*  -pretrazivanje gradova po drzavama po broju stanovnika-  */
int Pretraga_b(Pozicija_sdrzave root);
/*  -Trazi unesenu drzavu u stablu-  */
int Pronadi_Drzavu_S(Pozicija_sdrzave root, char ime_drzave[MAX]);
/*  -pronalazi i ispisuje sve gradove u zadanom randu broja stanovnika-  */
int Pronadi_I_Ispisi_Gradove_VL(Pozicija_VLgradovi head);

/*-------------------------------------------------MAIN FUNKCIJA-------------------------------------------------*/
int main()
{
    char odabir_opcije[MAX] = {'\0'};
    Ispis_Opcija(odabir_opcije);

    if (!strcmp(odabir_opcije, "a"))
    {
        /*deklaracija heada drzava*/
        VL_drzave head_drzava = {.ime_datoteke = {'\0'}, .ime_drzave = {'\0'}, .next = NULL, .root = NULL};
        Pozicija_ldrzave p_drzave_head = &head_drzava;

        Ucitaj_DrzaveVL(p_drzave_head);
        Pozicija_ldrzave drzava = NULL;
        drzava = p_drzave_head->next;
        while (drzava)
        {
            Ucitaj_Gradove_S(drzava);
            drzava = drzava->next;
        }

        Ispisi_Drzave_VL(p_drzave_head);
        Pretraga_a(p_drzave_head);
    }
    else if (!strcmp(odabir_opcije, "b"))
    {
        /*deklaracija roota drzava*/
        Pozicija_sdrzave p_drzave_root = NULL;

        p_drzave_root = Ucitaj_DrzaveS(p_drzave_root);
        Inorder_Drzave(p_drzave_root);

        Ispisi_Drzave_S(p_drzave_root);
        Pretraga_b(p_drzave_root);
    }

    return EXIT_SUCCESS;
}

/*------------------------------------------------OSTALE FUNCKIJE------------------------------------------------*/

int Ispis_Opcija(char *odabir_opcije)
{
    printf("\n Ukoliko zelite drzave unijeti u vezanu listu, a gradove u binarno stablo pretrazivanja upisite - \"a\"");
    printf("\n Ukoliko zelite drzave unijeti u binarno stablo pretrazivanja, a gradove u vezanu listu upisite - \"b\"");
    printf("\n Ukoliko zelite prekinuti program upisite \"exit\"\n");
    printf(" Unos odabira:\t");
    scanf(" %s", odabir_opcije);
    if (strcmp(odabir_opcije, "a") && strcmp(odabir_opcije, "b") && strcmp(odabir_opcije, "exit"))
    {
        system("cls");
        printf("\n Unijeli ste nepostojecu naredbu pokusajte ponovno!\n");
        Ispis_Opcija(odabir_opcije);
    }

    return EXIT_SUCCESS;
}

/*  --------------------------------------a) zadatak--------------------------------------  */
int Ucitaj_DrzaveVL(Pozicija_ldrzave head)
{
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
            head->next = Sortirani_unos_DrzaveVL(head->next, Nova_drzava);
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

int Ispisi_Drzave_VL(Pozicija_ldrzave head)
{
    Pozicija_ldrzave Lokacija = NULL;
    Lokacija = head->next;
    while (Lokacija)
    {
        printf("\n\n-----------------------------------------------------------");
        printf("\n%s:", Lokacija->ime_drzave);
        Ispisi_Gradove_S(Lokacija->root);
        Lokacija = Lokacija->next;
    }

    return EXIT_SUCCESS;
}

int Ispisi_Gradove_S(Pozicija_sgradovi root)
{
    Pozicija_sgradovi Lokacija = NULL;
    Lokacija = root;

    if (Lokacija)
    {
        Ispisi_Gradove_S(Lokacija->lijevo);
        printf("\n\t%s -> broj stanovnika: %d", Lokacija->ime_grada, Lokacija->broj_stanovnika);
        Ispisi_Gradove_S(Lokacija->desno);
        printf("\n");
    }

    return EXIT_SUCCESS;
}

int Pretraga_a(Pozicija_ldrzave head)
{
    char ime_drzave[MAX] = {'\0'};
    do
    {
        printf("\n-----------------------------------------------------------");
        printf("\n\n\nKojoj od unesenih drzava zelite pretraziti gradove po broju stanovnika?\n");
        printf("\nZa prekid pretrazivanja upisite \"exit\"\n");
        scanf(" %s", ime_drzave);
        Pronadi_Drzavu_VL(head, ime_drzave);
    } while (strcmp(ime_drzave, "exit") != 0);

    return EXIT_SUCCESS;
}

int Pronadi_Drzavu_VL(Pozicija_ldrzave head, char ime_drzave[MAX])
{
    Pozicija_ldrzave Lokacija = NULL;
    Lokacija = head->next;
    while (Lokacija)
    {
        if (!strcmp(ime_drzave, Lokacija->ime_drzave))
        {
            Pronadi_Gradove_S(Lokacija);

            break;
        }
        else
        {
            Lokacija = Lokacija->next;
        }
    }
    if (!Lokacija)
    {
        printf("\n%s se ne nalazi u vezanoj listi!\n", ime_drzave);
    }

    return EXIT_SUCCESS;
}

int Pronadi_Gradove_S(Pozicija_ldrzave Drzava)
{
    int min_broj_stanovnika = 0;
    Pozicija_sgradovi Lokacija = NULL;
    Lokacija = Drzava->root;
    printf("\n%s", Drzava->ime_drzave);
    printf("\nUnesite minimalan broj stanovnika gradova u odabranoj drzavi:\t");
    scanf("%d", &min_broj_stanovnika);
    Ispis_Gradova_S_min(Lokacija, min_broj_stanovnika);

    return EXIT_SUCCESS;
}

int Ispis_Gradova_S_min(Pozicija_sgradovi _Lokacija, int min_broj_stan)
{
    Pozicija_sgradovi Lokacija = NULL;
    Lokacija = _Lokacija;

    if (Lokacija)
    {
        if (Lokacija->broj_stanovnika <= min_broj_stan)
        {
            Ispis_Gradova_S_min(Lokacija->desno, min_broj_stan);
        }
        else
        {
            Ispis_Gradova_S_min(Lokacija->lijevo, min_broj_stan);
            printf("\n%s -> broj stanovnika: %d", Lokacija->ime_grada, Lokacija->broj_stanovnika);
            Ispis_Gradova_S_min(Lokacija->desno, min_broj_stan);
        }
    }

    return EXIT_SUCCESS;
}

/*  --------------------------------------b) zadatak--------------------------------------  */
Pozicija_sdrzave Ucitaj_DrzaveS(Pozicija_sdrzave root)
{
    FILE *fp = NULL;
    fp = fopen("drzave.txt", "r");
    if (!fp)
    {
        printf("\nNeuspjesno otvaranje datoteke:\t \"drzave.txt\"");
        return NULL;
    }
    while (!feof(fp))
    {
        Pozicija_sdrzave Nova_Drzava = NULL;
        Nova_Drzava = Nova_Drzava_S();
        if (Nova_Drzava)
        {
            fscanf(fp, " %s %s", Nova_Drzava->ime_drzave, Nova_Drzava->ime_datoteke);
            root = Sortirani_unos_DrzaveS(root, Nova_Drzava);
        }
    }

    return root;
}

Pozicija_sdrzave Nova_Drzava_S(void)
{
    Pozicija_sdrzave Nova_Drzava = NULL;
    Nova_Drzava = (Pozicija_sdrzave)malloc(sizeof(S_drzave));
    if (!Nova_Drzava)
    {
        printf("\nNEUSPJESNA ALOKACIJA MEMORIJE ZA NOVU DRZAVU!\n");
        return NULL;
    }
    Nova_Drzava->desno = NULL;
    Nova_Drzava->lijevo = NULL;
    Nova_Drzava->head = Novi_Grad_VL();

    return Nova_Drzava;
}

Pozicija_VLgradovi Novi_Grad_VL(void)
{
    Pozicija_VLgradovi Novi_Grad = NULL;
    Novi_Grad = (Pozicija_VLgradovi)malloc(sizeof(VL_gradovi));
    if (!Novi_Grad)
    {
        printf("\nNEUSPJESNA ALOKACIJA MEMORIJE ZA NOVI GRAD!\n");
        return NULL;
    }
    Novi_Grad->next = NULL;
    Novi_Grad->broj_stanovnika = 0;

    return Novi_Grad;
}

Pozicija_sdrzave Sortirani_unos_DrzaveS(Pozicija_sdrzave Lokacija, Pozicija_sdrzave Nova_Drzava)
{
    if (!Lokacija)
    {
        return Nova_Drzava;
    }
    if (strcmp(Lokacija->ime_drzave, Nova_Drzava->ime_drzave) < 0)
    {
        Lokacija->desno = Sortirani_unos_DrzaveS(Lokacija->desno, Nova_Drzava);

        return Lokacija;
    }
    else if (strcmp(Lokacija->ime_drzave, Nova_Drzava->ime_drzave) > 0)
    {
        Lokacija->lijevo = Sortirani_unos_DrzaveS(Lokacija->lijevo, Nova_Drzava);

        return Lokacija;
    }
    else
    {
        free(Nova_Drzava);

        return Lokacija;
    }
}

int Inorder_Drzave(Pozicija_sdrzave root)
{
    Pozicija_sdrzave Lokacija = NULL;
    Lokacija = root;

    if (Lokacija)
    {
        Inorder_Drzave(Lokacija->lijevo);
        Lokacija = Ucitaj_Gradove_VL(Lokacija);
        Inorder_Drzave(Lokacija->desno);
    }

    return EXIT_SUCCESS;
}

Pozicija_sdrzave Ucitaj_Gradove_VL(Pozicija_sdrzave Drzava)
{
    FILE *fp = NULL;
    fp = fopen(Drzava->ime_datoteke, "r");
    if (!fp)
    {
        printf("\nNeuspjesno otvaranje datoteke:\t \"drzave.txt\"");
        return NULL;
    }
    while (!feof(fp))
    {
        Pozicija_VLgradovi Novi_Grad = NULL;
        Novi_Grad = Novi_Grad_VL();
        if (Novi_Grad)
        {
            fscanf(fp, " %s %d", Novi_Grad->ime_grada, &Novi_Grad->broj_stanovnika);
            Drzava->head->next = Sortirani_Unos_GradoviVL(Drzava->head->next, Novi_Grad);
        }
    }

    return Drzava;
}

Pozicija_VLgradovi Sortirani_Unos_GradoviVL(Pozicija_VLgradovi Lokacija, Pozicija_VLgradovi Novi_Grad)
{
    if (!Lokacija)
    {
        return Novi_Grad;
    }

    if (Lokacija->broj_stanovnika < Novi_Grad->broj_stanovnika)
    {
        Lokacija->next = Sortirani_Unos_GradoviVL(Lokacija->next, Novi_Grad);

        return Lokacija;
    }
    else if (Lokacija->broj_stanovnika > Novi_Grad->broj_stanovnika)
    {
        Novi_Grad->next = Lokacija;

        return Novi_Grad;
    }
    else
    {
        if (strcmp(Lokacija->ime_grada, Novi_Grad->ime_grada) < 0)
        {
            Lokacija->next = Sortirani_Unos_GradoviVL(Lokacija->next, Novi_Grad);

            return Lokacija;
        }
        else if (strcmp(Lokacija->ime_grada, Novi_Grad->ime_grada) > 0)
        {
            Novi_Grad->next = Lokacija;

            return Novi_Grad;
        }
        else
        {
            free(Novi_Grad);
            return Lokacija;
        }
    }
}

int Ispisi_Drzave_S(Pozicija_sdrzave root)
{
    Pozicija_sdrzave Lokacija = NULL;
    Lokacija = root;

    if (Lokacija)
    {
        Ispisi_Drzave_S(Lokacija->lijevo);
        printf("\n\n-----------------------------------------------------------");
        printf("\n%s:", Lokacija->ime_drzave);
        Ispisi_Gradove_VL(Lokacija->head);
        Ispisi_Drzave_S(Lokacija->desno);
        printf("\n");
    }

    return EXIT_SUCCESS;
}

int Ispisi_Gradove_VL(Pozicija_VLgradovi head)
{
    Pozicija_VLgradovi Lokacija = NULL;
    Lokacija = head->next;

    while (Lokacija)
    {
        printf("\n\t%s -> broj stanovnika: %d", Lokacija->ime_grada, Lokacija->broj_stanovnika);
        Lokacija = Lokacija->next;
    }

    return EXIT_SUCCESS;
}

int Pretraga_b(Pozicija_sdrzave root)
{
    char ime_drzave[MAX] = {'\0'};
    do
    {
        printf("\n-----------------------------------------------------------");
        printf("\n\n\nKojoj od unesenih drzava zelite pretraziti gradove po broju stanovnika?\n");
        printf("\nZa prekid pretrazivanja upisite \"exit\"\n");
        scanf(" %s", ime_drzave);
        Pronadi_Drzavu_S(root, ime_drzave);
    } while (strcmp(ime_drzave, "exit") != 0);

    return EXIT_SUCCESS;
}

int Pronadi_Drzavu_S(Pozicija_sdrzave root, char ime_drzave[MAX])
{
    if (!root)
    {
        printf("\n%s se ne nalazi u stablu!\n", ime_drzave);
        return EXIT_FAILURE;
    }
    if (!strcmp(root->ime_drzave, ime_drzave))
    {
        Pronadi_I_Ispisi_Gradove_VL(root->head);
        printf("\n%s", root->ime_drzave);
    }
    else if (strcmp(root->ime_drzave, ime_drzave) < 0)
    {
        Pronadi_Drzavu_S(root->desno, ime_drzave);
    }
    else
    {
        Pronadi_Drzavu_S(root->lijevo, ime_drzave);
    }

    return EXIT_SUCCESS;
}

int Pronadi_I_Ispisi_Gradove_VL(Pozicija_VLgradovi head)
{
    Pozicija_VLgradovi Lokacija = NULL;
    Lokacija = head->next;
    int min_broj_stanovnika = 0;
    printf("\nUnesite minimalan broj stanovnika gradova u odabranoj drzavi:\t");
    scanf("%d", &min_broj_stanovnika);
    while (Lokacija)
    {
        if (Lokacija->broj_stanovnika > min_broj_stanovnika)
        {
            printf("\n%s -> broj stanovnika: %d", Lokacija->ime_grada, Lokacija->broj_stanovnika);
        }

        Lokacija = Lokacija->next;
    }

    return EXIT_SUCCESS;
}