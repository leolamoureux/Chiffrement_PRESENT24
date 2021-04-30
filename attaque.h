#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <math.h>

typedef struct ListeM{
    unsigned int **message;
    unsigned int **cle;
}ListeM;

typedef struct ListeC{
    unsigned int **message;
    unsigned int **cle;
}ListeC;

/*fonctions*/
ListeM init_M();
ListeC init_C();
ListeM remplir_liste_M(unsigned int message[24]);
ListeC remplir_liste_C(unsigned int message[24]);