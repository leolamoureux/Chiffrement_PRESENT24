#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>

unsigned long long *Liste_M;
unsigned long long *Liste_C;

/*fonctions*/
void remplir_liste_M(unsigned int message_clair, unsigned long long *liste);
void remplir_liste_C(unsigned int message_chiffre, unsigned long long *liste);
void tri_rapide (unsigned long long *tableau, int taille);
void compare_tab(unsigned long long *tab1, unsigned long long *tab2,int *liste_indices,int taille);
unsigned int double_chiffrement(unsigned int message_clair,unsigned int cle1,unsigned int cle2);
void attaque(unsigned int m1,unsigned int c1,unsigned int m2,unsigned int c2);
