#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128

/*DEKLARACIJA STRUKTURE DIREKTORIJA*/
struct _direktroij;
typedef struct _direktorij *Pozicija;
typedef struct _direktorij
{
    char naziv[MAX];
    Pozicija sibling;
    Pozicija child;
} direktorij;

/*DEKLARACIJA STRUKTURE STOGA*/
struct _Stog;
typedef struct _Stog *PozicijaStog;
typedef struct _Stog
{
    Pozicija Pointer;
    PozicijaStog next;
} Stog;

/*------------------------------------------DEKLARACIJA OTALIH FUNKCIJA------------------------------------------*/

/*  -ispisuje naredbe koje se smiju koristiti-  */
int Ispis_Opcija();
/*  poziva funkcije ovisno o unesenoj naredbi i vraca trenutni pokazivac  */
Pozicija Odabir_Opcije(char odabir[MAX], Pozicija root, char *path, PozicijaStog p_Stog);
/*  -sprema unesenu naredbu u string-   */
int Unos_Odabira(char odabir[MAX]);
/*  -omogucava unos novog pod-direktorija-  */
int Unos_Novog_PodDirektorija(Pozicija parent, Pozicija Novi_Dir);
/*  -alokacija memorije i stvaranje novog direktorija-  */
Pozicija Novi_Direktorij(char naziv[MAX]);
/*  -sortirani unos pod-direktorija koristenjem rekurzije-  */
Pozicija Sortiranje(Pozicija trenutni, Pozicija Novi_Dir);
/*  -ispisuje pod-direktorije s obzirom u kojem se direktoriju nalazimo-    */
int Ispis_PodDirektorija(Pozicija Lokacija, char *path);
Pozicija Otvaranje_PodDirektorija(Pozicija root, char naziv[MAX], char *path, PozicijaStog STOG_head);
/*  -nadopisuje na path naziv pod-direktorija kojeg otvorimo-   */
int UpisiPath(Pozicija Lokacija, char *naziv);
/*  -brise posljedni direktorij iz patha-   */
int IzbrisiZadnjiDioPatha(char *path);
/*  -na vrh stoga ubacuje pokazivac na direktorij-  */
int STOG_PUSH(Pozicija Direktorij, PozicijaStog STOG_head);
Pozicija STOG_POP(PozicijaStog STOG_head, char *path);
/*  -alokacija memorije i stvaranje novog elementa stoga-  */
PozicijaStog Novi_Element(Pozicija Direktorij);

/*-------------------------------------------------MAIN FUNKCIJA-------------------------------------------------*/

int main()
{
    char naredba[MAX] = {'\0'}; //unos naredbi
    char path[MAX] = {'\0'};    //string u koji se upisuje path

    /*  STRUKTURA ROOT - GLAVNI DIREKTORIJ "C:"   */
    direktorij struct_root = {.child = NULL, .naziv = "C:", .sibling = NULL};
    Pozicija p_root = NULL;
    p_root = &struct_root;
    strcpy(path, p_root->naziv);
    strcat(path, ">");

    /*  STOG KOJI POHRANJUJE POINTERE NA DIREKTORIJE    */
    Stog head = {.next = NULL, .Pointer = &struct_root};
    PozicijaStog p_Stog = &head;

    Ispis_Opcija();

    do
    {
        Unos_Odabira(naredba);
        p_root = Odabir_Opcije(naredba, p_root, path, p_Stog);
        if (strcmp(naredba, "exit") != 0)
        {
            printf("\n%s ", path);
        }
    } while (strcmp(naredba, "exit") != 0);

    return EXIT_SUCCESS;
}
/*------------------------------------------------OSTALE FUNCKIJE------------------------------------------------*/

int Ispis_Opcija()
{
    printf("\nMOGUCE NAREDBE ZA UREDIVANJE DIREKTORIJA:\n");
    printf("++++++++++++++++++++++++++++++++++++++++++\n\n");
    printf("\n\"md\" - unos novog pod-direktorija");
    printf("\n\"cd\" - ulazak u birani pod-direktorij");
    printf("\n\"cd ..\" - povratak na prethodni direktorij");
    printf("\n\"dir\" - ispis pod-direktorija");
    printf("\n\"exit\" -  gasenje programa\n");

    return EXIT_SUCCESS;
}

int Unos_Odabira(char *naredba)
{
    fgets(naredba, MAX, stdin);
    /*  ZAMJENJUJE '\n' sa '\0' NA KRAJU STRINGA  */
    if ((strlen(naredba) > 0) && (naredba[strlen(naredba) - 1] == '\n'))
    {
        naredba[strlen(naredba) - 1] = '\0';
    }

    return EXIT_SUCCESS;
}

Pozicija Odabir_Opcije(char naredba[MAX], Pozicija Lokacija, char *path, PozicijaStog p_Stog)
{
    Pozicija dir = NULL;
    dir = Lokacija;
    int regulator = 0; //regulira ponavljanje petlje... regulator !=0 sve dok korisnik unosi pogresnu naredbu
    do
    {
        char naziv[MAX] = {0}; //naziv pod-direktorija
        regulator = 0;

        /*----------------------"md ____"----------------------*/
        if ((naredba[0] == 'm' && naredba[1] == 'd') && (naredba[2] == ' ' || naredba[2] == '\0'))
        {
            if (naredba[2] == '\0' || naredba[3] == '\0')
            {
                printf("\nSintaksa ove naredbe je pogresna\n");
                Unos_Odabira(naredba);
                regulator = 1;
            }
            else
            {
                Pozicija q = NULL;
                memmove(naziv, naredba + 3, (strlen(naredba)));
                q = Novi_Direktorij(naziv);
                if (q)
                {
                    Unos_Novog_PodDirektorija(Lokacija, q);
                }
            }
        }

        /*----------------------"cd .."----------------------*/
        else if (strcmp(naredba, "cd ..") == 0)
        {
            dir = STOG_POP(p_Stog, path);
            if (dir == NULL)
            {
                dir = Lokacija;
            }
            else
            {
                Lokacija = dir;
                return Lokacija;
            }
        }

        /*----------------------"cd"----------------------*/
        else if ((naredba[0] == 'c' && naredba[1] == 'd') && (naredba[2] == ' ' || naredba[2] == '\0'))
        {
            if (naredba[3] == '\0' || naredba[2] == '\0') //ostaje na istom direktoriju
            {
                break;
            }
            else
            {
                memmove(naziv, naredba + 3, (strlen(naredba)));
                Lokacija = Otvaranje_PodDirektorija(Lokacija, naziv, path, p_Stog);
            }
        }

        /*----------------------"dir"----------------------*/
        else if (strcmp(naredba, "dir") == 0)
        {
            Ispis_PodDirektorija(Lokacija, path);
        }

        /*----------------------"exit"----------------------*/
        else if (strcmp(naredba, "exit") == 0)
        {
            system("cls");
        }

        else
        {
            printf("\n \"%s\" operacija nije prepoznata pokusajte ponovno:\n", naredba);
            Unos_Odabira(naredba);
            regulator = 1;
        }

    } while (regulator);

    return Lokacija;
}

int Unos_Novog_PodDirektorija(Pozicija parent, Pozicija Novi_Dir)
{
    Pozicija trenutni = NULL;
    trenutni = parent->child;
    parent->child = Sortiranje(trenutni, Novi_Dir);

    return EXIT_SUCCESS;
}

Pozicija Novi_Direktorij(char naziv[MAX])
{
    Pozicija Novi_Dir = NULL;
    Novi_Dir = (Pozicija)malloc(sizeof(direktorij));
    if (!Novi_Dir)
    {
        printf("\nNEUSPJESNA ALOKACIJA MEMORIJE ZA NOVI DIREKTORIJ!\n");
        return NULL;
    }
    Novi_Dir->sibling = NULL;
    Novi_Dir->child = NULL;
    strcpy(Novi_Dir->naziv, naziv);
    return Novi_Dir;
}

Pozicija Sortiranje(Pozicija trenutni, Pozicija Novi_Dir)
{
    if (trenutni == NULL)
    {
        return Novi_Dir;
    }
    if (strcmp(trenutni->naziv, Novi_Dir->naziv) < 0)
    {
        trenutni->sibling = Sortiranje(trenutni->sibling, Novi_Dir);
        return trenutni;
    }
    else if (strcmp(trenutni->naziv, Novi_Dir->naziv) > 0)
    {
        Novi_Dir->sibling = trenutni;
        return Novi_Dir;
    }
    else
    {
        free(Novi_Dir);
    }

    return trenutni;
}

int Ispis_PodDirektorija(Pozicija Lokacija, char *path)
{
    Pozicija pom = NULL;
    pom = Lokacija->child;
    if (Lokacija->child == NULL)
    {
        printf("\nDirektorij \"%s\"  nema unesenih pod-direktorija.\n", Lokacija->naziv);
    }
    else
    {
        printf("\n\t%s", path);
        while (pom)
        {
            printf("\n\t\t-%s", pom->naziv);
            pom = pom->sibling;
        }
    }
    printf("\n");
    return EXIT_SUCCESS;
}

Pozicija Otvaranje_PodDirektorija(Pozicija parent, char naziv[MAX], char *path, PozicijaStog STOG_head)
{
    Pozicija p_child = NULL;
    p_child = parent->child;

    if (!p_child)
    {
        printf("\nDirektorij \"%s\" je prazan", parent->naziv);
        return parent;
    }
    else
    {
        while (p_child && strcmp(p_child->naziv, naziv))
        {
            p_child = p_child->sibling;
        }
        if (p_child == NULL)
        {
            printf("\nDirektorij \"%s\" ne sadrzi pod-direktorij \"%s\"", parent->naziv, naziv);
            return parent;
        }
        else
        {
            UpisiPath(p_child, path);
            STOG_PUSH(p_child, STOG_head);
            return p_child;
        }
    }
}
int UpisiPath(Pozicija Lokacija, char *path)
{
    path[strlen(path) - 1] = '\\';
    strcat(path, Lokacija->naziv);
    strcat(path, ">");

    return EXIT_SUCCESS;
}

int IzbrisiZadnjiDioPatha(char *path)
{
    int duzina = 0;
    int i = 0;
    duzina = strlen(path);
    while (path[duzina] != '\\' && path[duzina] != ':')
    {
        path[duzina] = '\0';
        duzina--;
    }
    path[strlen(path) - 1] = '>';

    return EXIT_SUCCESS;
}

int STOG_PUSH(Pozicija Direktorij, PozicijaStog STOG_head)
{
    PozicijaStog noviElement = NULL;
    PozicijaStog pomoc = NULL;
    pomoc = STOG_head;

    while (pomoc->next)
    {
        pomoc = pomoc->next;
    }
    noviElement = Novi_Element(Direktorij);
    if (noviElement)
    {
        pomoc->next = noviElement;
    }
    return EXIT_SUCCESS;
}

Pozicija STOG_POP(PozicijaStog STOG_head, char *path)
{
    Pozicija dir = NULL; //pointer na prethodni direktorij
    PozicijaStog pomoc = NULL;
    pomoc = STOG_head->next;
    PozicijaStog prosli = NULL;
    prosli = STOG_head;
    if (!pomoc)
    {
        return NULL;
    }
    while (pomoc->next)
    {
        prosli = pomoc;
        pomoc = pomoc->next;
    }
    dir = prosli->Pointer;
    free(pomoc);
    prosli->next = NULL;
    IzbrisiZadnjiDioPatha(path);

    return dir;
}

PozicijaStog Novi_Element(Pozicija Direktorij)
{
    PozicijaStog NoviElement = NULL;
    NoviElement = (PozicijaStog)malloc(sizeof(Stog));
    if (!NoviElement)
    {
        printf("\nNEUSPJESNA ALOKACIJA MEMORIJE ZA NOVI ELEMENT STOGA!\n");

        return NULL;
    }
    else
    {
        NoviElement->Pointer = Direktorij;
        NoviElement->next = NULL;

        return NoviElement;
    }
}
