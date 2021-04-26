# include  <stdlib.h>
# include  <stdio.h>
# include  <string.h>

/*structure pour le cadencement des 11 clés*/
typedef struct cles{
    unsigned int K[11][24];
}CLES;
/////////////////////////////////////////////



//////liste des fonctions/////
void permutation(unsigned int message[24]);
void substitution(unsigned int message[24]);
void sub_4bits(unsigned int message[4]);
CLES cadencement(unsigned int cle[24]);
void chiffrement(unsigned int message[24],CLES k);
int comparaison_tableaux(int tab[], int k);
//////////////////////////////