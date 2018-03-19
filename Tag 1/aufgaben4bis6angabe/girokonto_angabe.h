#ifndef GIROKONTO_H_INCLUDED
#define GIROKONTO_H_INCLUDED

#include <stdio.h>

static int pufferFlag = 0;

#define PUFFER_ERROR -100

#define emptyInputStream {int c; do {c = getchar(); if (c == EOF) { pufferFlag = 1; return PUFFER_ERROR; } } while (c != '\n');}

#define clearLine(in) {int c; do {c = fgetc(in); if (c == EOF) { pufferFlag = 1; return PUFFER_ERROR; } } while (c != '\n');}

#define MAXNAME 30
#define MAXPUFFER 30
#define PUFFER_INVALID -101
#define PUFFER_OK 1
#define DISPO_MAX 10000.0

#define DISPO_OVERMAX -10
#define DISPO_OK 1

#define EROEFFNEN_NULL -20
#define EROEFFNEN_OK 1

#define NAME_KURZ -30
#define NAME_LANG -31
#define NAME_KLEIN -32
#define NAME_INVALID -33
#define NAME_OK 1

#define NUMMER_INVALID -40
#define NUMMER_NEGATIV -41

#define BETRAG_INVALID -50
#define BETRAG_NEGATIV -51

#define SUCHE_NEGATIV -60

#define SCHLIESSEN_MINUS -70
#define SCHLIESSEN_NULL -75
#define SCHLIESSEN_OK 1

#define AUSZAHLEN_NULL -80
#define AUSZAHLEN_LIMIT -81
#define AUSZAHLEN_OK 1

#define EINZAHLEN_NULL -90
#define EINZAHLEN_OK 1

#define PRINT_NULL -110
#define PRINT_EOF -111
#define PRINT_OK 1

#define SAVE_FAIL -120
#define SAVE_OK 1

#define LOAD_FAIL -130
#define LOAD_FORMAT_INV -131
#define LOAD_OK 1

#define LOAD_SNULL -141
#define LOAD_FEHLER -142
#define LOAD_FORMAT -143
#define SAVE_FEHLER -144
#define LOAD_NULL -145

/*Übung: Erfolgs- und Fehlerkonstanten Speichern*/

/*Übung: Erfolgs- und Fehlerkonstanten Laden*/

typedef struct _girokonto {
    char kontoinhaber[MAXNAME];
    int kontonummer;
    double saldo;
    double dispo;
} GIROKONTO;

typedef struct _kontoverwaltung {
    GIROKONTO * konten;
    int anzahl;
} KONTOVERWALTUNG;

int suche(int nummer, KONTOVERWALTUNG *v);
void printVerwaltung(KONTOVERWALTUNG *v);
int leseNummer();
double leseBetrag();
int leseName(char name[]);
KONTOVERWALTUNG * startVerwaltung();
void stopVerwaltung(KONTOVERWALTUNG *v);
int eroeffnen(char *name, double dispo, KONTOVERWALTUNG *v);
int schliessen(int found, KONTOVERWALTUNG * v);
int einzahlen(GIROKONTO *konto, double betrag);
int auszahlen(GIROKONTO *konto, double betrag);
int checkName(char *name);
int checkDispo(double dispo);
void ausdruck(GIROKONTO *konto);

/*Übung: Funktionen zum Speichern und Laden*/

int leseZeie(char puffer[], FILE *in);
int loadKonto(KONTOVERWALTUNG *v, FILE *in);
int load(KONTOVERWALTUNG *v, FILE *in);

#endif