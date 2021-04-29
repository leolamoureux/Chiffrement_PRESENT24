#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <math.h>

#define TAILLE_LISTE 100

/*2^24=16777216 clés possibles pour une taille de 24bits*/

/*liste M*/
typedef struct ListeM{
    unsigned int chiffre[TAILLE_LISTE][24];
    unsigned int cle[TAILLE_LISTE][24];
}ListeM;

/*Liste C*/
typedef struct ListeC{
    unsigned int clair[TAILLE_LISTE][24];
    unsigned int cle[TAILLE_LISTE][24];
}ListeC;

/*fonctions*/
ListeM remplir_liste_M(unsigned int message_clair[24]);
ListeC remplir_liste_C(unsigned int message_chiffre[24]);