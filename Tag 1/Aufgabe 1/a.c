#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	FILE *f;
	int i;

	srand(time(NULL));


	f = fopen("a01.txt", "w");

	if(f == NULL)
	{
		printf("Fehler beim erstellen der datei!\n");
		return 1;
	}
	else
		printf("Datei erfolgreich erstellt!\n");
	
	for(i = 0; i < 5; i++){
		if(fputc((rand() % 10) + '0', f) == EOF)
		{
			printf("Fehler beim schreiben!\n");
			return 1;
		}
	}

	if(fclose(f) == EOF){
		printf("Fehler beim schliessen der Datei!\n");
		return 1;	
	}

	f = fopen("a01.txt", "a");

	if(f == NULL)
	{
		printf("Fehler beim oeffnen der datei!\n");
		return 1;
	}

	if(fputs("ende", f) == EOF)
	{
		printf("Fehler beim schreiben in Datei!\n");
		return 1;
	}

	if(fclose(f) == EOF){
		printf("Fehler beim schliessen der Datei!\n");
		return 1;	
	}	


	return 0;
}