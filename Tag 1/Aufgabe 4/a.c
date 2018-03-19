#include <stdio.h>
#include <stdlib.h>

void close_exit(FILE *f, int exitvalue);


int main(void)
{
	FILE *f;
	int itmp;

	if((f = fopen("a01.txt", "r+")) == NULL)
	{
		printf("Fehler beim oeffnen der datei!\n");
		exit(1);
	}

	if(fseek(f, 4, SEEK_SET) != 0)
	{
		printf("Fehler bei seek!\n");
		close_exit(f, 1);
	}

	if(fputc('x', f) == EOF)
	{
		printf("Fehler beim schreiben!\n");
		close_exit(f, 1);
	}

	close_exit(f, -1);

	if((f = fopen("a01.txt", "r+")) == NULL)
	{
		printf("Fehler beim oeffnen der datei!\n");
		exit(1);
	}

	if(fseek(f, 0, SEEK_END) != 0)
	{
		printf("Fehler bei seek!\n");
		close_exit(f, 1);
	}

	if((itmp = ftell(f)) == -1L)
	{
		printf("Fehler bei ftell!\n");
		close_exit(f, 1);
	}


	if(fprintf(f, "%i", itmp) < 0)
	{
		printf("Fehler beim schreiben in Datei!\n");
		close_exit(f, 1);
	}

	close_exit(f, 0);

	return 0;
}

void close_exit(FILE *f, int exitvalue)
{
	if(fclose(f) == EOF)
		printf("Fehler beim schliessen\n");

	if(exitvalue == -1)
		return;
	exit(exitvalue);

}