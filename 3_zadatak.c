#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#define M 50
#define MAX 1024

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
int Dodaj_Na_Pocetak(Pozicija head, char *ime, char *prezime, int GodinaRodenja);   //1zadatak pod A)
int Ispisi_Listu(Pozicija prvi);                                                    //1zadatak pod B)
int Dodaj_Na_Kraj(Pozicija head, char *ime, char *prezime, int GodinaRodenja);      //1zadatak pod C)
Pozicija Pronadi_Zadnju(Pozicija head);
int Umetni_Nakon(Pozicija pozicija, Pozicija NovaOsoba);
Pozicija Nadi_Po_Prezimenu(Pozicija prvi, char *prezime);                           //1zadatak pod D)
int Obrisi_po_prezimenu(Pozicija head, char *prezime);                              //1zadatak pod E)
Pozicija Nadi_Prethodni(Pozicija head, char* prezime);
int Cita_Listu_Iz_Datoteke(Pozicija prvi);                                          //2zadatak pod E)
int Dodaj_iza(char *ime1, char *prezime1, int GodinaRodenja, char *prezime2, Pozicija prvi);//2zadatak pod A)
int Dodaj_prije(char *ime1, char *prezime1, int GodinaRodenja, char *prezime2, Pozicija head);//2zadatak pod B)
int sortiraj(Pozicija head);                                                        //2zadatak pod C)
int Unos_U_Datoteku(Pozicija head);                                                 //2zadatak pod D)
/*-------------------------------------------------MAIN FUNKCIJA-------------------------------------------------*/
int main()
{
    osoba head = { .next = NULL, .ime = {0}, .prezime = {0}, .GodinaRodenja = 0 };
    Pozicija p = &head;   
    Pozicija x = NULL;
    char odabir = '1';        //1 da zadovolji uvjet ulaska u while petlju
    char prezime_dodatno[M] =  {""};
    char Pom_Ime[M] = {""};
    char Pom_Prezime[M] = {""};
    int pom_god_rodenja = 0, prvi_odabir = 0;  
    printf("\nUkoliko prvo zelite ucitati vec postojecu datoteku odaberite broj 1:\t");
    scanf("%d", &prvi_odabir);
    printf("\n");
    if(prvi_odabir == 1)
    {
        Cita_Listu_Iz_Datoteke(p);
    }
    while(odabir != '0')
    {
        printf("\n\nKoji od programa zelite koristiti(Ako zelite prekinuti program odaberite '0':\n\n");
        printf("\nUkoliko zelite program koji:\n");
        printf("\n-\"dinamicki dodaje novi element na pocetak liste\" odaberite znak:\tA");   
        printf("\n-\"ispisuje listu\" odaberite znak:\tB");
        printf("\n-\"dinamicki dodaje novi element na kraj liste\" odaberite znak:\tC");
        printf("\n-\"pronalazi element u listi (po prezimenu)\" odaberite znak:\tD");
        printf("\n-\"brise odredeni element iz liste\" odaberite znak:\tE");
        printf("\n-\"dinamicki dodaje novi element iza odredenog elementa\tF");
        printf("\n-\"dinamicki dodaje novi element ispred odredenog elementa\tG\n");
        scanf(" %c", &odabir);
        system("cls");
        odabir=toupper(odabir);
        if(odabir == '0')
        {
            break;
        }
        if(odabir > 'G' || odabir < 'A')
        {
            do
            {
                printf("\nOdabrali ste nepostojeci program(\"%c\")\nPokusajte ponovno(A-E):\t", odabir);
                scanf(" %c", &odabir);
                odabir=toupper(odabir);           
            }while (odabir > 'G' || odabir < 'A');        
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
                if(x == NULL)
                {
                    printf("\nOsoba nije unesena u listu\n");
                }                
                else
                {
                    printf("\nIme:\t%s\nPrezime:\t%s\nGodina rodenja:\t%d", x->ime, x->prezime, x->GodinaRodenja );
                }
                break;
            case 'E':
                printf("\nUnesi prezime osobe koju zelite izbrisati:\t");
                scanf(" %s", Pom_Prezime);
                Obrisi_po_prezimenu(p, Pom_Prezime);
                break;
            case 'F':
                printf("\nUnesite podatke o osobi koju zelite unijeti u listu\n");
                printf("\nIme:\t");
                scanf(" %s", Pom_Ime);
                printf("\nPrezime:\t");
                scanf(" %s", Pom_Prezime);
                printf("\nGodina rodenja:\t");        
                scanf("%d", &pom_god_rodenja);
                printf("\n\nPrezime osobe iza koje zelite nadodati osobu - %s %s je? \n", Pom_Ime, Pom_Prezime);
                scanf(" %s", prezime_dodatno);
                Dodaj_iza(Pom_Ime, Pom_Prezime, pom_god_rodenja, prezime_dodatno, p->next);
                break;
            case 'G':
                printf("\nUnesite podatke o osobi koju zelite unijeti u listu\n");
                printf("\nIme:\t");
                scanf(" %s", Pom_Ime);
                printf("\nPrezime:\t");
                scanf(" %s", Pom_Prezime);
                printf("\nGodina rodenja:\t");        
                scanf("%d", &pom_god_rodenja);
                printf("\n\nPrezime osobe prije koje zelite nadodati osobu - %s %s je? \n", Pom_Ime, Pom_Prezime);
                scanf(" %s", prezime_dodatno);
                Dodaj_prije(Pom_Ime, Pom_Prezime, pom_god_rodenja, prezime_dodatno, p->next);
                break;    
            default:
                printf("\nGreska\n");
                break;
        }
    }
    printf("Lista prije sortiranja:\n\n");
    Ispisi_Listu(p);
    sortiraj(p);
    printf("\n\n\nLista nakon sortiranja:\n\n");
    Ispisi_Listu(p);
    Unos_U_Datoteku(p->next); 
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
    if (prvi->next == NULL)
	{
		printf("\nU listi nema elemenata!\n");
		return -1;
	}     
    Pozicija pomoc = prvi;        
    printf("%-25s %-25s %-25s\n\n","IME", "PREZIME", "GODINA RODENJA");
    while(pomoc->next)
    {        
        printf("\n%-25s %-25s %-25d", pomoc->next->ime, pomoc->next->prezime, pomoc->next->GodinaRodenja);
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
    {
		return -1;
    }
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

int Cita_Listu_Iz_Datoteke(Pozicija prvi)
{    
    Pozicija pomoc2 = NULL; 
    FILE *fp = NULL;
    char dat[M]={0};
    printf("\nUnesite naziv datoteke koju zelite procitati:\t");
    scanf(" %s", &dat);
    fp=fopen(dat,"r");
    if (fp == NULL)
    {
        printf("\nNIJE USPJELO OTVARANJE DATOTEKE -> %s\n", dat);
        return -1;
    }
    while (!feof(fp))
    {
        pomoc2 = (Pozicija)malloc(sizeof(osoba));
	    if (!pomoc2)
	    {
		    perror("\nAlokacija memorije neuspjesna!\n");
		    return -1;
	    }
        fscanf(fp, " %s %s %d", pomoc2->ime, pomoc2->prezime, &pomoc2->GodinaRodenja);        
        pomoc2->next=prvi->next;
        prvi->next=pomoc2;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
int Dodaj_iza(char *ime1, char *prezime1, int GodinaRodenja, char *prezime2, Pozicija prvi)
{
    Pozicija Glavna_osoba=NULL;
    Pozicija nova_osoba = NULL;
	nova_osoba = (Pozicija)malloc(sizeof(osoba));
	if (!nova_osoba)
	{
		perror("\nAlokacija memorije neuspjesna!\n");
		return -1;
	}	
	strcpy(nova_osoba->ime, ime1);
	strcpy(nova_osoba->prezime, prezime1);
	nova_osoba->GodinaRodenja = GodinaRodenja;
    Glavna_osoba = Nadi_Po_Prezimenu(prvi, prezime2);
    if(Glavna_osoba == NULL)
    {
        printf("\nOsoba %s nije unesena u listu\n", prezime2);
        return -1;
    }  
    nova_osoba->next=Glavna_osoba->next;
    Glavna_osoba->next=nova_osoba;
    return EXIT_SUCCESS;
}
int Dodaj_prije(char *ime1, char *prezime1, int GodinaRodenja, char *prezime2, Pozicija head)
{
    Pozicija Glavna_osoba=NULL;
    Pozicija nova_osoba = NULL;
	nova_osoba = (Pozicija)malloc(sizeof(osoba));
	if (!nova_osoba)
	{
		perror("\nAlokacija memorije neuspjesna!\n");
		return -1;
	}	
	strcpy(nova_osoba->ime, ime1);
	strcpy(nova_osoba->prezime, prezime1);
	nova_osoba->GodinaRodenja = GodinaRodenja;
    Glavna_osoba=Nadi_Prethodni(head, prezime2);
    if(Glavna_osoba == NULL)
    {
        return -1;
    }    
    nova_osoba->next=Glavna_osoba->next;
    Glavna_osoba->next=nova_osoba;
    return EXIT_SUCCESS;
}
int sortiraj(Pozicija head) //BUBBLE SORT
{
	Pozicija i, j, prosli_j, pomoc, kraj;
	kraj = NULL;
	i = head;
	while (i->next != kraj)
	{
		prosli_j = i;
		j = i->next;
		while (j->next != kraj)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
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
}

int Unos_U_Datoteku(Pozicija prvi)
{
    FILE *fp;
    char ime_datoteke[M];
    printf("\n\n\nKako zelite nazvati datoteku u koju upisujete listu?\n");
    scanf(" %s", ime_datoteke);
    fp=fopen(ime_datoteke, "w");
    if(fp == NULL)
    {
        printf("\nGreska u stvaranju nove datoteke!\n");
        return -1;
    }
    fprintf(fp, "\n %-25s %-25s %-25s \n\n", "IME", "PREZIME", "GODINA RODENJA");
    while (prvi != NULL)
		{
			fprintf(fp, "\n %-25s %-25s %-25d", prvi->ime, prvi->prezime, prvi->GodinaRodenja);
			prvi = prvi->next;
		}
    fclose(fp);
    printf("\nDatoteka %s uspjesno kreireana!\n", ime_datoteke);
    return 1;
}