#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 128
#define MAX_L 1024

/*DEKLARACIJA STRUKTURE STABLA*/
struct _stablo;
typedef struct _stablo *Pozicija;
typedef struct _stablo
{
    int broj;
    Pozicija lijevo;
    Pozicija desno;
} stablo;

/*------------------------------------------DEKLARACIJA OTALIH FUNKCIJA------------------------------------------*/

int IspisNaredbi();
int UnosNaredbe(char naredba[MAX]);
int OdabirOpcije(Pozicija head, char naredba[MAX], int broj);
Pozicija UnosNovogEl(Pozicija head, int broj);
Pozicija Novi_Element(int broj);
int InorderPrint(Pozicija head);
int PreorderPrint(Pozicija head);
int PostorderPrint(Pozicija head);
int Level_OrderPrint(Pozicija head, int izbor);
int DubinaStabla(Pozicija head);
int IspisiRazinu(Pozicija head, int razina);
Pozicija IzbrisiElement(Pozicija Lokacija, int izbor);
Pozicija PronadiMin(Pozicija Lokacija);
Pozicija PronadiEl(Pozicija Lokacija, int broj);

/*-------------------------------------------------MAIN FUNKCIJA-------------------------------------------------*/
int main()
{
    Pozicija p_stablo = NULL;

    char naredba[MAX] = {'\0'};
    int broj = 0;

    do
    {
        IspisNaredbi();
        broj = UnosNaredbe(naredba);
        printf("%d main broj", broj);

        OdabirOpcije(p_stablo, naredba, broj);
    } while (strcmp(naredba, "exit"));

    return EXIT_SUCCESS;
}
/*------------------------------------------------OSTALE FUNCKIJE------------------------------------------------*/

int IspisNaredbi()
{
    //system("cls");
    printf("\nMOGUCE OPERACIJE KORISITI UNOSOM SLJEDECIH NAREDBI\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n\"insert *broj*\" - Unosenje novog elementa");
    printf("\n\"inorder\" - Inorder ispis elemenata");
    printf("\n\"preorder\" - Preorder ispis elemenata");
    printf("\n\"postorder\" - Postorder ispis elemenata");
    printf("\n\"lvl_order\" - Level order ispis elemenata");
    printf("\n\"delete *broj*\" - Brisanje odredenog elementa");
    printf("\n\"find *broj*\" - Pronalazak odredenog elementa");
    printf("\n\"exit\" - Prekidanje programa\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    return EXIT_SUCCESS;
}
int UnosNaredbe(char naredba[MAX])
{
    int broj = 0;
    char stdin_string[MAX];
    printf("\n-->\t");
    fgets(stdin_string, MAX, stdin);
    /*  ZAMJENJUJE '\n' sa '\0' NA KRAJU STRINGA  */
    if ((strlen(stdin_string) > 0) && (stdin_string[strlen(stdin_string) - 1] == '\n'))
    {
        stdin_string[strlen(stdin_string) - 1] = '\0';
    }
    sscanf(stdin_string, "%s %d", naredba, &broj);
    printf(", %d sscanf broj", broj);

    return broj;
}

int OdabirOpcije(Pozicija head, char naredba[MAX], int broj)
{
    Pozicija Lokacija = NULL;
    int regulator = 0; //regulira ponavljanje petlje... regulator !=0 sve dok korisnik unosi pogresnu naredbu

    do
    {
        printf("\n1.naredba->%s, broj -> %d\n", naredba, broj);
        regulator = 0;
        Lokacija = head;
        /*----------------------"insert ____"----------------------*/
        if (!strcmp(naredba, "insert"))
        {
            printf("\tinorder %d", broj);
            Lokacija = UnosNovogEl(Lokacija, broj);
        }
        else if (!strcmp(naredba, "inorder"))
        {
            InorderPrint(head);
        }
        else if (!strcmp(naredba, "preorder"))
        {
            PreorderPrint(head);
        }
        else if (!strcmp(naredba, "postorder"))
        {
            PostorderPrint(head);
        }
        else if (!strcmp(naredba, "lvlorder"))
        {
            int izbor = 0;
            printf("\nKoju razinu binarnog stabla pretrazivanja zelite ispisati?");
            printf("\nUkoliko zelite ispisati cijelo binarno stablo pretrazivanje upisite broj 0");
            printf("\nBROJ:\t");
            scanf("%d", &izbor);
            printf("\n");
            Level_OrderPrint(Lokacija, izbor);
            int x = strlen(naredba);
            for (int i = 0; i < x; i++)
            {
                naredba[i] = '\0';
            }
        }
        else if (!strcmp(naredba, "delete"))
        {
            Lokacija = IzbrisiElement(Lokacija, broj);
            int x = strlen(naredba);
            for (int i = 0; i < x; i++)
            {
                naredba[i] = '\0';
            }
        }
        else if (!strcmp(naredba, "find"))
        {
            Lokacija = PronadiEl(Lokacija, broj);
            if (!Lokacija)
            {
                printf("\nElement %d nije pronaden!\n", broj);
            }
            else
            {
                printf("\nElement %d je pronaden!\n", broj);
            }
        }
        else if (!strcmp(naredba, "exit"))
        {
            return EXIT_SUCCESS;
        }
        else
        {
            printf("\n-9-\n");
            printf("\n \"%s\" operacija nije prepoznata pokusajte ponovno:\n", naredba);
            broj = UnosNaredbe(naredba);
            regulator = 1;
        }
        //printf("\nnaredba->%s, broj -> %d\n", naredba, broj);
    } while (regulator);

    return EXIT_SUCCESS;
}

Pozicija UnosNovogEl(Pozicija head, int broj)
{
    Pozicija Lokacija = NULL;
    Lokacija = head;
    Pozicija NoviElement = NULL;

    if (!Lokacija)
    {
        NoviElement = Novi_Element(broj);
        return NoviElement;
    }

    else if (broj < Lokacija->broj)
    {
        Lokacija->lijevo = UnosNovogEl(Lokacija->lijevo, broj);
    }

    else if (broj > Lokacija->broj)
    {
        Lokacija->desno = UnosNovogEl(Lokacija->desno, broj);
    }

    else
    {
        free(NoviElement);
    }

    return Lokacija;
}

Pozicija Novi_Element(int broj)
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

int InorderPrint(Pozicija head)
{
    Pozicija Lokacija = NULL;
    Lokacija = head;

    if (Lokacija)
    {
        InorderPrint(Lokacija->lijevo);
        printf("%d, ", Lokacija->broj);
        InorderPrint(Lokacija->desno);
    }

    return EXIT_SUCCESS;
}

int PreorderPrint(Pozicija head)
{
    Pozicija Lokacija = NULL;
    Lokacija = head;

    if (Lokacija)
    {
        printf("%d, ", Lokacija->broj);
        PreorderPrint(Lokacija->lijevo);
        InorderPrint(Lokacija->desno);
    }

    return EXIT_SUCCESS;
}

int PostorderPrint(Pozicija head)
{
    Pozicija Lokacija = NULL;
    Lokacija = head;

    if (Lokacija)
    {
        PostorderPrint(Lokacija->lijevo);
        PostorderPrint(Lokacija->desno);
        printf("%d, ", Lokacija->broj);
    }

    return EXIT_SUCCESS;
}

int Level_OrderPrint(Pozicija head, int izbor)
{
    int dubina = DubinaStabla(head);
    int pocetak = 1;

    if (izbor == 0)
    {
        while (pocetak <= dubina)
        {
            IspisiRazinu(head, pocetak);
            pocetak++;
            printf("\n");
        }
    }

    else
    {
        IspisiRazinu(head, izbor);
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

Pozicija IzbrisiElement(Pozicija Lokacija, int izbor)
{
    Pozicija pom = NULL;
    Pozicija _Lokacija = NULL;
    _Lokacija = Lokacija;

    if (!_Lokacija)
    {
        printf("\nU ovom binarnom stablu pretrazivanja ne postoji broj %d\n", izbor);
    }
    else if (_Lokacija->broj > izbor)
    {
        _Lokacija->lijevo = IzbrisiElement(_Lokacija->lijevo, izbor);
    }
    else if (_Lokacija->broj < izbor)
    {
        _Lokacija->desno = IzbrisiElement(_Lokacija->desno, izbor);
    }
    else if (_Lokacija->lijevo && _Lokacija->desno)
    {
        pom = PronadiMin(_Lokacija->desno);
        _Lokacija->broj = pom->broj;
        _Lokacija->desno = IzbrisiElement(_Lokacija->desno, _Lokacija->broj);
    }
    else
    {
        pom = _Lokacija;
        if (!_Lokacija->lijevo)
        {
            _Lokacija = _Lokacija->desno;
        }
        else
        {
            _Lokacija = _Lokacija->lijevo;
        }
        free(pom);
    }

    return _Lokacija;
}

Pozicija PronadiMin(Pozicija Lokacija)
{
    Pozicija _lokacija = NULL;
    _lokacija = Lokacija;

    while (_lokacija->lijevo)
    {
        _lokacija = _lokacija->lijevo;
    }

    return _lokacija;
}

Pozicija PronadiEl(Pozicija Lokacija, int broj)
{
    Pozicija _lokacija = NULL;
    _lokacija = Lokacija;

    if (!_lokacija)
    {
        return NULL;
    }

    else if (_lokacija->broj > broj)
    {
        return PronadiEl(_lokacija->lijevo, broj);
    }
    else if (_lokacija->broj < broj)
    {
        return PronadiEl(_lokacija->desno, broj);
    }

    return _lokacija;
}