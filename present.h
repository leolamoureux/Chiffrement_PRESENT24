#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct cles{
    unsigned long long K[11];
}CLES;

int hexa_to_dec(char *mot);
int substitution(int etat);
int substitution_inverse(int etat);
int permutation(int etat);
int permutation_inverse(int etat);
CLES cadencement(int cle_maitre);
int chiffrement(int message_clair,CLES cles);
int dechiffrement(int message, CLES cles);

