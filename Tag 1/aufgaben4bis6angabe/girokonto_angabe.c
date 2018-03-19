#include "girokonto_angabe.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int suche(int nummer, KONTOVERWALTUNG * v) {
    int i;
    for(i = 0; i < v->anzahl; ++i) {
        if(((v->konten)[i]).kontonummer == nummer)
            return i;
    }
    return SUCHE_NEGATIV;
}

int leseNummer() {
	int nummer;
	if(scanf("%i", &nummer) != 1 || getchar() != '\n') {
        	emptyInputStream;
        	return NUMMER_INVALID;
     }
    	else if(nummer < 0) 
		return NUMMER_NEGATIV;
    	return nummer;
}

double leseBetrag() {
	double zahl;
	if(scanf("%lf", &zahl) != 1 || getchar() != '\n') {
        	emptyInputStream;
        	return BETRAG_INVALID;
    	}
    	else if(zahl < 0) 
		return BETRAG_NEGATIV;
    	return zahl;
}

int leseName(char name[]) {
	int i = 0;
	int c;
	
	do {
		c = getchar();
		if (c == EOF) {
			pufferFlag = 1;
			return PUFFER_ERROR;
		}
		if (c == '\n')
			break;
		name[i] = c;
	} while (i++ < MAXNAME - 1);
	
	if (i == MAXNAME) {
		emptyInputStream;
		return NAME_INVALID;
	}
	
	name[i] = '\0';
	return NAME_OK;
}

KONTOVERWALTUNG * startVerwaltung() {
    KONTOVERWALTUNG * v = malloc(sizeof(KONTOVERWALTUNG));
    if (v == NULL) return NULL;
    v->konten = NULL;
    v->anzahl = 0;
    return v;
}

void stopVerwaltung(KONTOVERWALTUNG * v){
    if(v->anzahl > 0)
        free(v->konten);
    free(v);
}

int eroeffnen(char *name, double dispo, KONTOVERWALTUNG * v){
    static int neuenummer = 1000;
    GIROKONTO * neu;
    int status;

    status = checkName(name);
    if (status != NAME_OK)
        return status;
    
    status = checkDispo(dispo);
    if (status != DISPO_OK)
        return status;
    
    if(v->anzahl == 0) {
        neu = malloc(sizeof(GIROKONTO));
        if (neu == NULL) 
		return EROEFFNEN_NULL;
    }
    else {
        neu = realloc(v->konten, (v->anzahl + 1) * sizeof(GIROKONTO));
        if (neu == NULL) 
		return EROEFFNEN_NULL;
    }
    v->konten = neu;
    ++(v->anzahl);

    neu = &(v->konten)[v->anzahl - 1];    
    strcpy(neu->kontoinhaber, name);
    neu->dispo = dispo;
    neu->kontonummer = neuenummer++;
    neu->saldo = 0.0;

    return EROEFFNEN_OK;

}

int schliessen(int found, KONTOVERWALTUNG * v) {
    GIROKONTO * konto;
    GIROKONTO * neu;
    konto = &(v->konten)[found];
    if(konto->saldo < 0.0)
        return SCHLIESSEN_MINUS;
    auszahlen(konto, konto->saldo);
    *konto = (v->konten)[v->anzahl - 1];
    --(v->anzahl);
    if(v->anzahl == 0)
        v->konten = NULL;
    else {
        neu = realloc(v->konten, (v->anzahl)*sizeof(GIROKONTO));
        if (neu == NULL) 
		return SCHLIESSEN_NULL;
        v->konten = neu;
    }
    return SCHLIESSEN_OK;
}

int einzahlen(GIROKONTO *konto, double betrag) {
    if (konto == NULL)
        return EINZAHLEN_NULL;
    (konto->saldo) += betrag;
    return EINZAHLEN_OK;
}

int auszahlen(GIROKONTO *konto, double betrag) {
    if (konto == NULL)
        return AUSZAHLEN_NULL;
    if(konto->saldo + konto->dispo < betrag)
        return AUSZAHLEN_LIMIT;
    konto->saldo -= betrag;
    return AUSZAHLEN_OK;
}

int checkName(char *name) {
    if (strlen(name) < 2)
        return NAME_KURZ;
    if (strlen(name) > MAXNAME - 1)
        return NAME_LANG;
    if (!isupper(*name))
        return NAME_KLEIN;
    return NAME_OK;
}

int checkDispo(double dispo) {
    if (dispo > DISPO_MAX)
        return DISPO_OVERMAX;
    return DISPO_OK;
}

void printVerwaltung(KONTOVERWALTUNG * v) {
    int i;
    for(i = 0; i < v->anzahl; ++i) {
        ausdruck(&((v->konten)[i]));
    }
}

void ausdruck(GIROKONTO *konto) {
    if (konto == NULL)
        return;
    printf("Kontonummer: %i\n", konto->kontonummer);
    printf("Kontoinhaber: %s\n", konto->kontoinhaber);
    printf("Aktueller Saldo: %.2f\n", konto->saldo);
    printf("Aktueller Dispo: %.2f\n\n", konto->dispo);
}

int leseZeile(char puffer[], FILE *in){
    int i;
    int input;
    for(i = 0; i < MAXPUFFER; i++)
    {
        input = fgetc(in);
        if(input == EOF && !feof(in))
            return PRINT_EOF;
        if(input == EOF || input == '\n'){
            break;
        }

        puffer[i] = input;
    }

    if(i == MAXPUFFER){
        emptyInputStream;
        return PUFFER_INVALID;
    }
    puffer[i] = '\0';
    return PUFFER_OK;
}

int loadKonto(KONTOVERWALTUNG *v, FILE *in)
{
    char buffer[MAXPUFFER];
    GIROKONTO tmpkonto;

    if(fscanf(in, "%i", &(tmpkonto.kontonummer)) != 1)
        return LOAD_FAIL;

    if(leseZeile(buffer, in) != PUFFER_OK)
        return PUFFER_INVALID;

    printf("%s\n", buffer);
    if(checkName(buffer) != NAME_OK)
        return NAME_INVALID;

    strcpy(tmpkonto.kontoinhaber, buffer);

    if(fscanf(in, "%lf", &(tmpkonto.dispo)) != 1)
        return LOAD_FAIL;

    if(fscanf(in, "%lf", &(tmpkonto.saldo)) != 1)
        return LOAD_FAIL;

    if(eroeffnen(tmpkonto.kontoinhaber, tmpkonto.dispo, v) != EROEFFNEN_OK)
        return LOAD_FAIL;

    v->konten[v->anzahl - 1].kontonummer = tmpkonto.kontonummer;
    v->konten[v->anzahl - 1].saldo = tmpkonto.saldo;

    return LOAD_OK;
}

int load(KONTOVERWALTUNG *v, FILE *in)
{
    char buffer[MAXPUFFER];
    if(leseZeile(buffer, in) != PUFFER_OK)
        return LOAD_FAIL;
    if(strcmp(buffer, "Ende") == 0)
        return LOAD_OK;

    while(1)
    {
        if(strcmp(buffer, "Neu") != 0)
            return LOAD_FORMAT_INV;

        if(loadKonto(v, in) != LOAD_OK)
            return LOAD_FAIL;

        if(leseZeile(buffer, in) != PUFFER_OK)
            return PUFFER_INVALID;

        if(strcmp(buffer, "Ende") == 0)
            return LOAD_OK;
    }


}