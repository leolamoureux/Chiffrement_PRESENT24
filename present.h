#include <stdio.h>
#include <string.h>
#include <math.h>

/*structure pour stocker les 11 clé de cadencement*/
typedef struct cles{
    unsigned long long K[11];
}CLES;

/*liste des fonctions*/
int hexa_to_dec(char *mot);
int substitution(int etat);
int substitution_inverse(int etat);
int permutation(int etat);
int permutation_inverse(int etat);
CLES cadencement(int cle_maitre);
int chiffrement(int message_clair,CLES cles);
int dechiffrement(int message, CLES cles);

