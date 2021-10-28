#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#define M 50

struct _Osoba;
typedef struct _Osoba* Pozicija;
typedef struct _Osoba{
    char ime[M];
    char prezime[M];
    int GodinaRodenja;
    Pozicija next;
}osoba;

/*------------------------------------------DEKLARACIJA OTALIH FUNKCIJA------------------------------------------*/
/*osoba Stvori_Osobu(char *ime, char *prezime, int GodinaRodenja);*/
int Dodaj_Na_Pocetak(Pozicija head, char *ime, char *prezime, int GodinaRodenja);   //zadatak pod A)
int Ispisi_Listu(Pozicija prvi);                                                    //zadatak pod B)
int Dodaj_Na_Kraj(Pozicija head, char *ime, char *prezime, int GodinaRodenja);    //zadatak pod C)
Pozicija Pronadi_Zadnju(Pozicija head);
int Umetni_Nakon(Pozicija pozicija, Pozicija NovaOsoba);
Pozicija Nadi_Po_Prezimenu(Pozicija prvi, char *prezime);                           //zadatak pod D)
int Obrisi_po_prezimenu(Pozicija head, char *prezime);                              //zadatak pod E)
Pozicija Nadi_Prethodni(Pozicija head, char* prezime);

/*-------------------------------------------------MAIN FUNKCIJA-------------------------------------------------*/
int main()
{
    osoba head = { .next = NULL, .ime = {0}, .prezime = {0}, .GodinaRodenja = 0 };
    Pozicija p = &head;   
    Pozicija x= NULL;
    char odabir='1';        //1 da zadovolji uvjet ulaska u while petlju
    char Pom_Ime[M]={""};
    char Pom_Prezime[M]={""};
    int pom_god_rodenja=0;  
    while(odabir != '0')
    {
        printf("\n\nKoji od programa zelite koristiti(Ako zelite prekinuti program odaberite '0':\n\n");
        printf("\nUkoliko zelite program koji:\n");
        printf("\n-\"dinamicki dodaje novi element na pocetak liste\" odaberite znak:\tA");   
        printf("\n-\"ispisuje listu\" odaberite znak:\tB");
        printf("\n-\"dinamicki dodaje novi element na kraj liste\" odaberite znak:\tC");
        printf("\n-\"pronalazi element u listi (po prezimenu)\" odaberite znak:\tD");
        printf("\n-\"brise odredeni element iz liste\" odaberite znak:\tE\n");
        scanf(" %c", &odabir);
        system("cls");
        odabir=toupper(odabir);
        if(odabir == '0')
        {
            break;
        }
        if(odabir > 'E' || odabir < 'A')
        {
            do
            {
                printf("\nOdabrali ste nepostojeci program(\"%c\")\nPokusajte ponovno(A-E):\t", odabir);
                scanf(" %c", &odabir);
                odabir=toupper(odabir);           
            }while (odabir > 'E' || odabir < 'A');        
        }   
        switch ((char)odabir)
        {
        case 'A':
            printf("\nUnesite podatke o osobi\n");
            printf("\nIme:\t");
            scanf(" %s", Pom_Ime);
            printf("\nPrezime:\t");
            scanf(" %s", Pom_Prezime);
            printf("\nGodina rodenja:\t");        
            scanf("%d", &pom_god_rodenja);
            Dodaj_Na_Pocetak(p, Pom_Ime, Pom_Prezime, pom_god_rodenja);
            break;
        case 'B':
            Ispisi_Listu(p);
            printf("\n\n");
            break;
        case 'C':
            printf("\nUnesite podatke o osobi\n");
            printf("\nIme:\t");
            scanf(" %s", Pom_Ime);
            printf("\nPrezime:\t");
            scanf(" %s", Pom_Prezime);
            printf("\nGodina rodenja:\t");        
            scanf("%d", &pom_god_rodenja);
            Dodaj_Na_Kraj(p, Pom_Ime, Pom_Prezime, pom_god_rodenja);
            break;
        case 'D':
            printf("\nUnesite prezime koje zelite pronaci:\t");    
            scanf(" %s", Pom_Prezime);
            x=Nadi_Po_Prezimenu(p, Pom_Prezime);
            printf("\nIme:\t%s\nPrezime:\t%s\nGodina rodenja:\t%d", x->ime, x->prezime, x->GodinaRodenja );
            break;
        case 'E':
            printf("\nUnesi prezime osobe koju zelite izbrisati:\t");
            scanf(" %s", Pom_Prezime);
            Obrisi_po_prezimenu(p, Pom_Prezime);
            break;    
        default:
            printf("\nGreska\n");
            break;
        }
    }
    return EXIT_SUCCESS;
}

/*------------------------------------------------OSTALE FUNCKIJE------------------------------------------------*/
int Dodaj_Na_Pocetak(Pozicija head, char *ime, char *prezime, int GodinaRodenja)
{
    Pozicija nova_osoba = NULL;
	nova_osoba = (Pozicija)malloc(sizeof(osoba));
	if (!nova_osoba)
	{
		perror("\nAlokacija memorije neuspjesna!\n");
		return -1;
	}	
	strcpy(nova_osoba->ime, ime);
	strcpy(nova_osoba->prezime, prezime);
	nova_osoba->GodinaRodenja = GodinaRodenja;
	nova_osoba->next = NULL;
	nova_osoba->next = head->next;
	head->next = nova_osoba;
    return EXIT_SUCCESS;
}

int Ispisi_Listu(Pozicija prvi)
{
    char IME[M]={"IME"}, 
        PREZIME[M]={"PREZIME"},
        Godina[M]={"GODINA_RODENJA"};
    if (prvi->next == NULL)
	{
		printf("\nU listi nema elemenata!\n");
		return -1;
	}     
    Pozicija pomoc = prvi;        
    printf("%-25s %-25s %-25s\n\n",IME, PREZIME, Godina);
    while(pomoc)
    {
        printf("\n%-25s %-25s %-25d", pomoc->ime, pomoc->prezime, pomoc->GodinaRodenja);
        pomoc=pomoc->next;
    }
    return EXIT_SUCCESS;
}

int Dodaj_Na_Kraj(Pozicija head, char *ime, char *prezime, int GodinaRodenja)
{
    Pozicija nova_osoba = NULL;
    Pozicija zadnji = NULL;
    Pozicija p = head;
	nova_osoba = (Pozicija)malloc(sizeof(osoba));
	if (!nova_osoba)
	{
		perror("\nAlokacija memorije neuspjesna!\n");
		return -1;
	}
    strcpy(nova_osoba->ime, ime);
	strcpy(nova_osoba->prezime, prezime);
	nova_osoba->GodinaRodenja = GodinaRodenja;
    zadnji = Pronadi_Zadnju(p);
    Umetni_Nakon(zadnji, nova_osoba);
    return EXIT_SUCCESS;
}

Pozicija Pronadi_Zadnju(Pozicija head)
{
    Pozicija pomocna = head;

	while (pomocna->next)
	{
		pomocna = pomocna->next;
	}
	return pomocna;    
}

int Umetni_Nakon(Pozicija pozicija, Pozicija NovaOsoba)
{
    NovaOsoba->next = NULL;
    pozicija->next = NovaOsoba;
    return EXIT_SUCCESS;
}

Pozicija Nadi_Po_Prezimenu(Pozicija prvi, char *prezime)
{
    Pozicija Pomocna = prvi;
	while (Pomocna)
	{
		if (strcmp(Pomocna->prezime, prezime) == 0)
		{
			return Pomocna;
		}
		Pomocna = Pomocna->next;
	}
	return NULL;
}

int Obrisi_po_prezimenu(Pozicija head, char *prezime)
{
    Pozicija prosli = NULL;
	Pozicija trenutni = NULL;
	prosli = Nadi_Prethodni(head, prezime);

	if (prosli == NULL)
		return -1;

	trenutni = prosli->next;
	prosli->next = prosli->next->next;
	free(trenutni);

	return EXIT_SUCCESS;    
}

Pozicija Nadi_Prethodni(Pozicija head, char* prezime)
{
    Pozicija prosli = NULL, trenutni = NULL;
	prosli = head;
	trenutni = prosli->next;
	while (trenutni != NULL && strcmp(trenutni->prezime, prezime) != 0)
	{
		prosli = trenutni;
		trenutni = prosli->next;
	}
	if (trenutni == NULL) 
    { 
		printf("\nOsoba nije upuisana u listu\n");
		return NULL;
	}
	return prosli;
}