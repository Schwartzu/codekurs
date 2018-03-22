#ifndef KRYPTO_H_INCLUDED
#define KRYPTO_H_INCLUDED

int is_text_upper_case(const char *text);
char *caesar(char key, const char *text, int coding_mode);
char *vigenere(const char *key, const char *text, int coding_mode);
void brute_caesar(const char *code, char *file);
char freq_analysis(const char *code);

int *distances(const char *code);
int ggT_distances(const int *distances, int n);

char *kasiski(const char *code);

#define ENCODING 10
#define DECODING 20

#define SYMBOL_N 7

#endif