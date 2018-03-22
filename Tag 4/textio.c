#include <stdio.h>
#include <stdlib.h>

#include "textio.h"

char *read_text(const char *file)
{
	int file_size = 0, i = 0;
	char *text;
	int c;
	FILE *text_file = fopen(file, "r");
	if (text_file == NULL) {
		fprintf(stderr, "read_text: failed to open %s", file);
		return NULL;
	}
	fseek(text_file, 0L, SEEK_END);
	file_size = ftell(text_file);
	rewind(text_file);
	text = malloc(file_size + 1);
	if (text == NULL) {
		fprintf(stderr, "read_text: malloc failed");
		fclose(text_file);
		return NULL;
	}
	while ((c = getc(text_file)) != EOF) {
		if (c != '\n' && c != ' ' && c != '\0') {
			text[i] = c;
			++i;
		}
	}
	fclose(text_file);
	text[i] = '\0';
	return text;
}

int write_text(const char *text, const char *file)
{
	FILE *text_file = fopen(file, "wa+");
	if (text_file == NULL) {
		fprintf(stderr, "write_text: failed to open %s", file);
		return 0;
	}
	while (*(text) != '\0') {
		fputc((int)(*(text)), text_file);
		++text;
	}
	fclose(text_file);
	return 1;
}
