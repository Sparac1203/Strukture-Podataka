#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

#define MAX 1024

/*DEKLARACIJA STRUKTURE*/
struct _Stog;
typedef struct _Stog *Pozicija;
typedef struct _Stog
{
    float element;
    Pozicija next;
} Stog;

/*------------------------------------------DEKLARACIJA OTALIH FUNKCIJA------------------------------------------*/
int Citanje_Iz_Datoteke(Pozicija head);
Pozicija Push(Pozicija, float);
float Pop(Pozicija);
int Racunanje_Izraza(Pozicija, char);

/*-------------------------------------------------MAIN FUNKCIJA-------------------------------------------------*/
int main()
{
    Stog head = {.element = 0, .next = NULL};
    Pozicija p = &head;
    Citanje_Iz_Datoteke(p);
    printf("\nRezultat matematickih operacija koristenjem postfiksa je:\t%.4f\n\n", p->next->element);

    return EXIT_SUCCESS;
}

/*------------------------------------------------OSTALE FUNCKIJE------------------------------------------------*/
Pozicija Push(Pozicija head, float broj)
{
    Pozicija q;
    q = (Pozicija)malloc(sizeof(Stog));
    if (!q)
    {
        perror("\nAlokacija memorije neuspjesna!\n");
        return NULL;
    }
    q->next = head->next;
    head->next = q;
    q->element = broj;

    return q;
}

float Pop(Pozicija head)
{
    float Broj = 0.0;
    Pozicija temp;
    temp = head->next;

    Broj = temp->element;
    head->next = temp->next;
    free(temp);

    return Broj;
}

int Citanje_Iz_Datoteke(Pozicija head)
{
    char *ime_dat;
    char buffer[MAX];
    char *pokbuf = buffer;
    ime_dat = (char *)malloc(sizeof(char) * MAX);
    FILE *fp = NULL;
    printf("\nIz koje datoteke zelite ucitati polinome?\n");
    scanf(" %s", ime_dat);
    fp = fopen(ime_dat, "r");
    if (fp == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke %s !\n", ime_dat);
        return EXIT_FAILURE;
    }
    fgets(buffer, MAX, fp);
    fclose(fp);
    while (strlen(pokbuf) > 0)
    {
        char operacija = 0;
        float broj = 0;
        int pomak = 0;
        if (sscanf(pokbuf, " %f%n", &broj, &pomak) == 1)
        {
            Push(head, broj);
            pokbuf += pomak;
        }
        else
        {
            sscanf(pokbuf, " %c %n", &operacija, &pomak);
            Racunanje_Izraza(head, operacija);
            pokbuf += pomak;
        }
    }

    return EXIT_SUCCESS;
}

int Racunanje_Izraza(Pozicija head, char operacija)
{
    float br1=0.0;
    float br2=0.0;
    switch (operacija)
    {
    case '+':
        br1 = Pop(head);
        br2 = Pop(head);
        Push(head, br1 + br2);
        break;

    case '-':
        br1 = Pop(head);
        br2 = Pop(head);
        Push(head, br2 - br1);
        break;

    case '*':
        br1 = Pop(head);
        br2 = Pop(head);
        Push(head, br2 * br1);
        break;

    case '/':
        br1 = Pop(head);
        br2 = Pop(head);
        if (br1 == 0)
            printf("\nDijeljenje s 0 nije dozvoljeno!");
        else
            Push(head, br2 / br1);
        break;
    }

    return EXIT_SUCCESS;
}