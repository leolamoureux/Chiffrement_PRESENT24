#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <math.h>

typedef struct ListeM{
    unsigned int *message[24];
    unsigned int *cle[24];
}ListeM;

typedef struct ListeC{
    unsigned int *message[24];
    unsigned int *cle[24];
}ListeC;

/*fonctions*/
ListeM init_M();
ListeC init_C();
ListeM remplir_liste_M(unsigned int message[24]);
ListeC remplir_liste_C(unsigned int message[24]);