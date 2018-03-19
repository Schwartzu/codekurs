#include <stdio.h>
#include "girokonto_loesung.h"

void printHauptMenu() {
    printf("\nHauptmenu (Eingaben mit Enter-Taste abschliessen)\n");
    printf("-------------------------------------------------\n");
    printf("n - Neues Konto anlegen\n");
    printf("s - Konto schliessen\n");
    printf("e - Einzahlung verbuchen\n");
    printf("a - Auszahlung verbuchen\n");
    printf("k - Kontostand abfragen\n");
    printf("d - Dispokredit neu festlegen\n");
    printf("p - Alle Konten anzeigen\n");
    printf("x - Speichern\n");
    printf("l - Laden\n");
    printf("q - Programm beenden\n");
    printf("--------------------\n");
    printf("Ihre Auswahl: ");    
}

void printFehler(char * fehler) {
    printf("\nEs ist ein Fehler aufgetreten\n");
    printf("------------------------------\n");
    puts(fehler);
    printf("\n");
    
}

void printStatus(int status) {
    switch(status) {
        case(EROEFFNEN_NULL):
            printFehler("Speicherreservierung fehlgeschlagen");
            break;
        case(NUMMER_INVALID):
            printFehler("Keine gueltige Nummer");
            break;
        case(NUMMER_NEGATIV):
            printFehler("Nummer ist negativ");
            break;
        case(BETRAG_INVALID):
            printFehler("Kein gueltiger Betrag");
            break;
        case(BETRAG_NEGATIV):
            printFehler("Betrag ist negativ");
            break;
        case(NAME_INVALID):
            printFehler("Kein gueltiger Name");
            break;
        case(NAME_KURZ):
            printFehler("Name ist zu kurz");
            break;
        case(NAME_LANG):
            printFehler("Name ist zu lang");
            break;
        case(NAME_KLEIN):
            printFehler("Name beginnt nicht mit Grossbuchstaben");
            break;
        case(DISPO_OVERMAX):
            printFehler("Dispo ist zu gross");
            break;
        case(EINZAHLEN_NULL):
            printFehler("Konto nicht vorhanden");
            break;
        case(AUSZAHLEN_NULL):
            printFehler("Konto nicht vorhanden");
            break;
        case(AUSZAHLEN_LIMIT):
            printFehler("Auszahlung ueberschreitet Dispokredit");
            break;
        case(SCHLIESSEN_MINUS):
            printFehler("Kontostand ist negativ");
            break;
        case(PUFFER_ERROR):
            printFehler("Pufferfehler");
            break;

		/*Fehlernachrichten für Fehler beim Laden und Speichern*/
        case(LOAD_NULL):
            printFehler("Keine Kontoverwaltung");
            break;
        case(LOAD_SNULL):
            printFehler("Keine Kontoverwaltung");
            break;
        case(LOAD_FEHLER):
            printFehler("Lesefehler");
            break;
        case(LOAD_FORMAT):
            printFehler("Formatfehler");
            break;
        case(SAVE_FEHLER):
            printFehler("Schreibfehler");
            break;

        default:
            printFehler("Unbekannter Fehler");
    }
}

void printLoadMenu() {
    printf("\nDateiname eingeben (Eingaben mit Enter-Taste abschliessen)\n");
    printf("-------------------------------------------------------------------\n");
    printf("Ihre Eingabe: ");
}

/*Neues Menu für Eingabe des Dateinamens zum Speichern oder Laden*/
void printSaveMenu() {
    printf("\nDateiname eingeben (Eingaben mit Enter-Taste abschliessen)\n");
    printf("-------------------------------------------------------------------\n");
    printf("Ihre Eingabe: ");
}

void printNameMenu() {
    printf("\nName Kontoinhaber eingeben (Eingaben mit Enter-Taste abschliessen)\n");
    printf("-------------------------------------------------------------------\n");
    printf("Ihre Eingabe: ");
}

void printDispoMenu() {
    printf("\nDispo eingeben (Eingaben mit Enter-Taste abschliessen)\n");
    printf("------------------------------------------------------\n");
    printf("Ihre Eingabe: ");
}

void printKontoMenu() {
    printf("\nKontonummer eingeben (Eingaben mit Enter-Taste abschliessen)\n");
    printf("------------------------------------------------------\n");
    printf("Ihre Eingabe: ");
}

void printBetragMenu() {
    printf("\nBetrag eingeben (Eingaben mit Enter-Taste abschliessen)\n");
    printf("------------------------------------------------------\n");
    printf("Ihre Eingabe: ");
}

void printBye() {
    printf("\nDas Programm wird beendet\n");
}

int isCommand(char *c) {
    int c1,c2;
    if ((c1 = getchar()) == EOF) {
        pufferFlag = 1;
        return PUFFER_ERROR;
    }
    if (c1 == '\n') {
        printFehler("Kein gueltiges Kommandoformat (Zeichen + Enter)");
        return 0;
    }
    if ((c2 = getchar()) == EOF) {
        pufferFlag = 1;
        return PUFFER_ERROR;
    }
    if(c2!='\n') {
        printFehler("Kein gueltiges Kommandoformat (Zeichen + Enter)");
        emptyInputStream;
        return 0;
    }
    *c = c1;
    return 1;
}

int main() {
	KONTOVERWALTUNG * verwaltung;
    	GIROKONTO * konto;
    
	FILE * datei; /*Zugriff auf Datei zum Speichern oder Laden*/
    
	char name[MAXNAME];
    	char cwert;
    	double dwert;
    	int iwert;
    
	int gespeichert = 1;
	
    verwaltung = startVerwaltung();
    if(verwaltung == NULL) {
        printFehler("Verwaltung konnte nicht initialisiert werden");
        return 1;
    }
    
    while(1) {
		if(pufferFlag) {
			printFehler("Pufferfehler (Programm wird abgebrochen)");
			stopVerwaltung(verwaltung);
			return 1;
		}
		printHauptMenu();
		if(isCommand(&cwert) != 1) continue;
		switch(cwert) {
			case('n'):
                		printNameMenu();
                		iwert = leseName(name);
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		printDispoMenu();
                		dwert = leseBetrag();
                		if(dwert < 0) {
                    		printStatus((int) dwert);
                    		continue;
                		}
				iwert = eroeffnen(name, dwert, verwaltung);
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		gespeichert = 0;
                		printf("Konto eroeffnet!\n");
                		printf("Alle Konten:\n");
                		printVerwaltung(verwaltung);
				break;
			case('s'):
                		printKontoMenu();
                		iwert = leseNummer();
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		iwert = suche(iwert, verwaltung);
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
				iwert = schliessen(iwert, verwaltung);
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		gespeichert = 0;
                		printf("Konto geschlossen!\n");
                		printf("Alle Konten:\n");
                		printVerwaltung(verwaltung);
				break;
			case('e'):
                		printKontoMenu();
                		iwert = leseNummer();
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		iwert = suche(iwert, verwaltung);
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		konto = &(verwaltung->konten)[iwert];
                		printBetragMenu();
                		dwert=leseBetrag();
                		if(dwert < 0) {
                    		printStatus((int) dwert);
                    		continue;
                		}
                		iwert = einzahlen(konto, dwert);
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		gespeichert = 0;
                		printf("Betrag eingezahlt!\n");
                		printf("Alle Konten:\n");
                		printVerwaltung(verwaltung);
				break;
			case('a'):
                		printKontoMenu();
                		iwert = leseNummer();
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		iwert = suche(iwert, verwaltung);
                		if(iwert < 0){
                    		printStatus(iwert);
                    		continue;
                		}
                		konto = &(verwaltung->konten)[iwert];
                		printBetragMenu();
                		dwert=leseBetrag();
                		if(dwert < 0) {
                    		printStatus((int)dwert);
                    		continue;
                		}
                		iwert = auszahlen(konto,dwert);
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		gespeichert = 0;
                		printf("Betrag ausgezahlt!\n");
                		printf("Alle Konten:\n");
                		printVerwaltung(verwaltung);
				break;
			case('k'):
                		printKontoMenu();
                		iwert = leseNummer();
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		iwert = suche(iwert, verwaltung);
                		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		konto = &(verwaltung->konten)[iwert];
                		ausdruck(konto);
				break;
			case('d'):
                		printKontoMenu();
                		iwert = leseNummer();
               		if(iwert < 0) {
                    		printStatus(iwert);
                    		continue;
                		}
                		iwert = suche(iwert, verwaltung);
                		if(iwert < 0){
                    		printStatus(iwert);
                    		continue;
                		}
                		konto = &(verwaltung->konten)[iwert];
                		printDispoMenu();
                		dwert=leseBetrag();
                		if(dwert < 0) {
                    		printStatus((int) dwert);
                    		continue;
                		}
                		iwert = checkDispo(dwert);
                		if(iwert < 0) {
                   		printStatus(iwert);
                    		continue;
                		}
                		konto->dispo = dwert;
                		gespeichert = 0;
                		printf("Dispo neu gesetzt!\n");
                		printf("Alle Konten:\n");
                		printVerwaltung(verwaltung);
				break;
			case('p'):
				printf("Alle Konten:\n");
			    	printVerwaltung(verwaltung);
				break;

			/*Übung: Kommando zum Speichern*/
			case('x'):
				break;

			/*Kommando zum Laden*/
			case('l'):

				/*Sind aktuelle Daten abgespeichert?*/
                		if (gespeichert == 0) {
                    		printf("\nZuerst aktuelle Konten speichern\n");
                    		continue;
                		}

				/*Verwaltung neu starten*/
                		stopVerwaltung(verwaltung);
                		verwaltung = startVerwaltung();
                		if(verwaltung == NULL) {
                    		printFehler("Verwaltung konnte nicht initialisiert werden");
                    		return 1;
                		}

				/*Dateinamen einlesen*/
                		printLoadMenu();
                		iwert=leseName(name);
                		if(iwert < 0) {
                    		printFehler("Eingabe Dateiname ungueltig");
                    		continue;
                		}

				/*Datei zu Dateinamen öffnen*/
                		datei = fopen(name, "r");
                		if (datei == NULL) {
                    		printf("\nDatei exitiert nicht!\n");
                    		continue;
                		}

				/*Daten aus Datei laden*/				
                		iwert = load(verwaltung, datei);
                		if(iwert < 0) {
                    		printStatus(iwert);
                		}

				/*Datei schließen*/
                		if (fclose(datei) != 0) {
                    		printFehler("Fehler beim Schliessen der Datei");
                    		continue;
                		}
                		gespeichert = 1;
                		printf("Konten geladen\n");
                		printf("Alle Konten:\n");
                		printVerwaltung(verwaltung);
				break;

			case('q'):
                		if (gespeichert == 0) { 
                    		printf("\nZuerst aktuelle Konten speichern\n");
                    		continue;
                		}
				printBye();
                		stopVerwaltung(verwaltung);
                		return 0;
				break;
			default:
				printFehler("Kein gueltiges Kommando");
		}
	}
}
