# include  <stdlib.h>
# include  <stdio.h>
# include  <string.h>
/*
struct message{
    char *M;
    int taille; //taille du message
    };

struct cle{
    char *K;
    int taille; //taille de la clé
    };

struct boite_s{
    int bit1;
    int bit2;
    int bit3;
    int bit4;
    };

typedef struct cle CLE;
typedef struct message MESSAGE;
typedef struct boite_s BOITE_S;
*/

////////////////Listes des fonctions////////////////

char *chiffrement(char *message, char *cle);
char *substitution(char *message);
char *permutation(char *message);
char  XOR(int a, int b);
void boite_s(int bit1,int bit2, int bit3, int bit4);