#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>

unsigned long *Liste_M;
unsigned long *Liste_C;

/*fonctions*/
void remplir_liste_M(int message_clair, int *liste);
void remplir_liste_C(int message_chiffre, int *liste);
void tri_rapide (int *tableau, int taille);
void compare_tab(int *tab1, int *tab2,int *liste_indices,int taille);
int double_chiffrement(int message_clair,int cle1,int cle2);
void attaque(int message_clair,int message_chiffre);
