#include <stdio.h>
#include <stdlib.h>

void close_exit(FILE *f, int returnvalue);


int main(void)
{
	FILE *f;
	int i;
	char input;

	if((f = fopen("a01.txt", "r")) == NULL)
	{
		printf("Fehler beim oeffnen der datei!\n");
	}

	for(i = 0; i < 4; i++)
	{
		if((input = fgetc(f)) == EOF){
			printf("Fehler beim lesen (EOF)\n");
			close_exit(f, 1);
		}
		putchar(input);
	}

	if(fseek(f, -6, SEEK_END) != 0)
	{
		printf("Fehler bei seek!\n");
		close_exit(f, 1);
	}

	for(i = 0; i < 6; i++)
	{
		if((input = fgetc(f)) == EOF)
		{
			printf("Fehler beim lesen der Datei");
			close_exit(f, 1);
		}

		putchar(input);
	}

	close_exit(f, 0);

	return 0;
}

void close_exit(FILE *f, int returnvalue)
{
	if(fclose(f) == EOF)
		printf("Fehler beim schliessen\n");

	exit(returnvalue);

}