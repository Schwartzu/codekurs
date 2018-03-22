#ifndef KRYPTO_H_INCLUDED
#define KRYPTO_H_INCLUDED

int is_text_upper_case(const char *text);
char *caesar(char key, const char *text, int coding_mode);
char *vigenere(const char *key, const char *text, int coding_mode);


#define ENCODING 10
#define DECODING 20

#endif