#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXbr 90
#define MINbr 10

/*DEKLARACIJA STRUKTURE STABLA*/
struct _stablo;
typedef struct _stablo *Pozicija;
typedef struct _stablo
{
    int broj;
    Pozicija lijevo;
    Pozicija desno;
} stablo;

/*DEKLARACIJA STRUKTURE REDA*/
struct _Red;
typedef struct _Red *PozicijaRed;
typedef struct _Red
{
    int broj;
    PozicijaRed next;
} Red;

/*------------------------------------------DEKLARACIJA OTALIH FUNKCIJA------------------------------------------*/

/*  -postavlja uneseni broj na odredeno mjesto u binarnom stavlu-   */
Pozicija insert(Pozicija head, int novi_broj);
/*  -alocira memoriju za novostvoreni element-  */
Pozicija Stvori_Novi_Element(int broj);
/*  -svaki element stabla zamijenjuje sumom elemenata u njegovom lijevom i desnom podstablu -  */
int replace(Pozicija trenutna_Lokacija);
/*  -zbraja elemente podstabla (ukljucuje element korijena stabla)-  */
int Zbroji(Pozicija Lokacija);
/*  -ispisuje binarno stablo (LEVEL ORDER)-  */
int Level_OrderPrint(Pozicija head);
/*  -pronalazi broj razina od kojih se sastoji binarno stablo-  */
int DubinaStabla(Pozicija head);
/*  -ispisuje pojedinu razinu binarnog stabla-  */
int IspisiRazinu(Pozicija head, int razina);
/*  -U novi niz upisuje slucajne brojeve-  */
int Punjenje_rand(int niz[], int velicina, PozicijaRed Red_head);
/*  -Stavlja broj 'na vrh' reda-  */
int RED_PUSH(PozicijaRed Head, int broj);
/*  -Skida prvi clan reda-  */
int RED_POP(PozicijaRed Head);
/*  -Elemente iz binarnog stabla ubacuje u red(INORDER)-  */
int Inorder(Pozicija Stablo_head, PozicijaRed Red_head);
/*  -Upisuje u datoteku sadrzaj reda-  */
int Upisi_U_File(PozicijaRed head, int regulator);
/*  -alocira memoriju za novostvoreni element reda-  */
PozicijaRed RED_Stvori_Novi_Element(int broj);

/*-------------------------------------------------MAIN FUNKCIJA-------------------------------------------------*/
int main()
{
    srand(time(NULL));
    int regulator = 0;
    Red head = {.broj = 0, .next = NULL};
    PozicijaRed red_head = &head;
    Pozicija p_stablo = NULL;
    Pozicija p_stablo_rand = NULL;
    int Zadani_Niz[] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
    int *NoviNiz;
    NoviNiz = (int *)malloc(sizeof(Zadani_Niz));

    /*PRVO BINARNO STABLO (SADRZI VEC ZADANE BROJEVE)*/
    printf("\nBinarno stablo prije sumiranja podstabala:\n");
    for (int i = 0; i < (sizeof(Zadani_Niz) / sizeof(int)); i++)
    {
        p_stablo = insert(p_stablo, Zadani_Niz[i]);
    }
    Level_OrderPrint(p_stablo);
    p_stablo->broj = replace(p_stablo);
    printf("\nBinarno stablo nakon sumiranja podstabala:\n");
    Level_OrderPrint(p_stablo);

    /*DRUGO BINARNO STABLO (SADRZI NASUMICNE BROJEVE OD 10 DO 90)*/
    Punjenje_rand(NoviNiz, sizeof(Zadani_Niz) / sizeof(int), red_head);
    for (int i = 0; i < (sizeof(Zadani_Niz) / sizeof(int)); i++)
    {
        p_stablo_rand = insert(p_stablo_rand, NoviNiz[i]);
    }
    Inorder(p_stablo_rand, red_head);
    Upisi_U_File(red_head, regulator);
    regulator++;
    printf("\n \n");
    printf("\nSlucajno generirano binarno stablo prije sumiranja podstabala:\n");
    Level_OrderPrint(p_stablo_rand);
    printf("\nSlucajno generirano binarno stablo nakon sumiranja podstabala:\n");
    p_stablo_rand->broj = replace(p_stablo_rand);
    Level_OrderPrint(p_stablo_rand);
    Inorder(p_stablo_rand, red_head);
    Upisi_U_File(red_head, regulator);

    return EXIT_SUCCESS;
}

/*------------------------------------------------OSTALE FUNCKIJE------------------------------------------------*/

Pozicija insert(Pozicija head, int novi_broj)
{
    Pozicija Lokacija = NULL;
    Lokacija = head;

    Pozicija NoviElement = NULL;

    if (!Lokacija)
    {
        NoviElement = Stvori_Novi_Element(novi_broj);

        return NoviElement;
    }
    else if (novi_broj >= Lokacija->broj)
    {
        Lokacija->lijevo = insert(Lokacija->lijevo, novi_broj);
    }
    else
    {
        Lokacija->desno = insert(Lokacija->desno, novi_broj);
    }

    return Lokacija;
}

Pozicija Stvori_Novi_Element(int broj)
{
    Pozicija NoviElement = NULL;
    NoviElement = (Pozicija)malloc(sizeof(stablo));
    if (!NoviElement)
    {
        printf("\nNEUSPJESNA ALOKACIJA MEMORIJE ZA NOVI ELEMENT!\n");

        return NULL;
    }
    NoviElement->broj = broj;
    NoviElement->desno = NULL;
    NoviElement->lijevo = NULL;

    return NoviElement;
}

int replace(Pozicija trenutna_Lokacija)
{
    int zbroj = 0;
    if (trenutna_Lokacija)
    {
        zbroj = Zbroji(trenutna_Lokacija) - trenutna_Lokacija->broj;
        if (trenutna_Lokacija->lijevo)
        {
            trenutna_Lokacija->lijevo->broj = replace(trenutna_Lokacija->lijevo);
        }
        if (trenutna_Lokacija->desno)
        {
            trenutna_Lokacija->desno->broj = replace(trenutna_Lokacija->desno);
        }
    }

    return zbroj;
}

int Zbroji(Pozicija Lokacija)
{
    if (Lokacija)
    {
        return (Lokacija->broj + Zbroji(Lokacija->desno) + Zbroji(Lokacija->lijevo));
    }
    else
    {
        return 0;
    }
}

int Level_OrderPrint(Pozicija head)
{
    int dubina = DubinaStabla(head);
    int pocetak = 1;

    while (pocetak <= dubina)
    {
        IspisiRazinu(head, pocetak);
        pocetak++;
        printf("\n");
    }

    return EXIT_SUCCESS;
}

int DubinaStabla(Pozicija head)
{
    int Dubina_L = 0;
    int Dubina_D = 0;

    if (!head)
    {
        return 0;
    }

    else
    {
        Dubina_D = DubinaStabla(head->desno);
        Dubina_L = DubinaStabla(head->lijevo);

        return (Dubina_L > Dubina_D) ? (Dubina_L + 1) : (Dubina_D + 1);
    }
}

int IspisiRazinu(Pozicija head, int razina)
{
    Pozicija Lokacija = NULL;
    Lokacija = head;
    if (!head)
    {
        printf("\\\t");
        return EXIT_SUCCESS;
    }
    if (razina == 1)
    {
        printf("%d\t", head->broj);
    }
    else if (razina > 1)
    {
        IspisiRazinu(head->lijevo, razina - 1);
        IspisiRazinu(head->desno, razina - 1);
    }

    return EXIT_SUCCESS;
}

int Punjenje_rand(int niz[], int velicina, PozicijaRed Red_head)
{
    for (int i = 0; i < velicina; i++)
    {
        niz[i] = rand() % (MAXbr + 1 - MINbr) + MINbr;
    }

    return EXIT_SUCCESS;
}

int RED_PUSH(PozicijaRed Head, int broj)
{
    PozicijaRed noviElement = NULL;
    PozicijaRed pomoc = NULL;
    pomoc = Head;

    while (pomoc->next)
    {
        pomoc = pomoc->next;
    }
    noviElement = RED_Stvori_Novi_Element(broj);
    if (noviElement)
    {
        pomoc->next = noviElement;
    }

    return EXIT_SUCCESS;
}

int RED_POP(PozicijaRed Head)
{
    int broj = 0;
    PozicijaRed prvi_element = NULL;
    PozicijaRed drugi_element = NULL;
    if (Head->next)
    {
        prvi_element = Head->next;
        drugi_element = Head->next->next;
        broj = prvi_element->broj;
        Head->next = drugi_element;
        free(prvi_element);
        return broj;
    }
    else
    {
        return -1;
    }
}

int Inorder(Pozicija Stablo_head, PozicijaRed Red_head)
{
    Pozicija Lokacija = NULL;
    Lokacija = Stablo_head;

    if (Lokacija)
    {
        Inorder(Lokacija->lijevo, Red_head);
        RED_PUSH(Red_head, Lokacija->broj);
        Inorder(Lokacija->desno, Red_head);
    }

    return EXIT_SUCCESS;
}

int Upisi_U_File(PozicijaRed head, int regulator)
{
    int brojac = 1;
    FILE *fp = NULL;
    char naziv_dat[] = {"inorder.txt"};

    /*REGULATOR <= 0 AKO U DATOTEKU UNOSIMO INORDER ISPIS STABLA PRIJE SUMIRANJA PODSTABALA*/
    if (!regulator)
    {
        fp = fopen(naziv_dat, "w");
        fputs("Binarno stablo prije sumiranja podstabala:\n", fp);
        while (brojac != -1)
        {
            brojac = RED_POP(head);
            if (brojac != -1)
            {
                fprintf(fp, "%d, ", brojac);
            }
        }
        fputs("\n", fp);
        fclose(fp);
    }
    
    /*REGULATOR > 0 AKO U DATOTEKU UNOSIMO INORDER ISPIS STABLA NAKON SUMIRANJA PODSTABALA*/
    else
    {
        fp = fopen(naziv_dat, "a");
        fputs("\nBinarno stablo nakon sumiranja podstabala:\n", fp);
        while (brojac != -1)
        {
            brojac = RED_POP(head);
            if (brojac != -1)
            {
                fprintf(fp, "%d, ", brojac);
            }
        }
        fputs("\n", fp);
        fclose(fp);
    }
    
    return EXIT_SUCCESS;
}

PozicijaRed RED_Stvori_Novi_Element(int broj)
{
    PozicijaRed NoviElement = NULL;
    NoviElement = (PozicijaRed)malloc(sizeof(stablo));
    if (!NoviElement)
    {
        printf("\nNEUSPJESNA ALOKACIJA MEMORIJE ZA NOVI ELEMENT!\n");

        return NULL;
    }
    NoviElement->broj = broj;
    NoviElement->next = NULL;

    return NoviElement;
}