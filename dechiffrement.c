#include "dechiffrement.h"

unsigned int boite_S_inverse[16][4]={{0,1,0,1},//5
                             {1,1,1,0},//e
                             {1,1,1,1},//f
                             {1,0,0,0},//8
                             {1,1,0,0},//c
                             {0,0,0,1},//1
                             {0,0,1,0},//2
                             {1,1,0,1},//d
                             {1,0,1,1},//b
                             {0,1,0,0},//4
                             {0,1,1,0},//6
                             {0,0,1,1},//3
                             {0,0,0,0},//0
                             {0,1,1,1},//7
                             {1,0,0,1},//9
                             {1,0,1,0}};//a
                             
int permutation_tab_inverse[24]={0,6,12,18,1,7,13,19,2,8,14,20,
                         3,9,15,21,4,10,16,22,5,11,17,23};

void dechiffrement(unsigned int message[24],CLES k){
    unsigned int etat[24];
    for(int i=0;i<24;i++){
        etat[i]=message[i]; /* Etat ← m */
    }
    for(int x=0;x<24;x++){ /*etat XOR K11*/
             etat[x]=etat[x] ^ k.K[10][x];/* Etat ← Etat ⊕ K11 */
        }    
    for(int i=1;i<=10;i++){ /* pour i = 1 jusqu’a 10 faire */
        permutation(etat);  /* Etat ← Permutation(Etat) */
        substitution(etat); /* Etat ← Substitution(Etat)*/
        for(int j=0;j<24;j++){
            etat[j]=etat[j] ^ k.K[i-1][j];/* Etat ← Etat ⊕ Ki*/
        }
    }
    for(int i=0;i<24;i++){
        message[i]=etat[i]; /*c(message) ← Etat */
    }
    /*retourne message*/
}