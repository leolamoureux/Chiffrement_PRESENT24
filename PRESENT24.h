# include  <stdlib.h>
# include  <stdio.h>
# include  <string.h>

/*structure pour le cadencement des 11 clés*/
typedef struct cles{
    unsigned int K[11][24];
}CLES;
/////////////////////////////////////////////

///////////fonctions de chiffrement//////////
void permutation(unsigned int message[24]);/*fonction de permutation*/
void substitution(unsigned int message[24]);/*fonction de substitution d'un message de 24 bits*/
void sub_4bits(unsigned int message[4]);/*fonction de substitution d'un message de 4 bits*/
CLES cadencement(unsigned int cle[24]);/*fonction qui retourne 11 clé de 24 bits*/
void chiffrement(unsigned int message[24],CLES k);/*fonction qui chiffre un message avec 11 clés*/
int comparaison_tableaux(int tab[], int k);/*fonction utilisé pour la substitution*/
/////////////////////////////////////////////

//////////fonctions de conversion////////////
void bits_to_hexa(unsigned int message[24]);/*convertir un message de 24bits en un message en hexa*/
void hexa_to_bits(char *mot_hexa,unsigned int message_destination[24]);/*convertir un message en hexa en un message de 24 bits*/
/////////////////////////////////////////////