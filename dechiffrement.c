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
                             
int permutation_tab_inverse[24]={0,4,8,12,16,20,1,5,9,13,17,21,2,6,10,14,18,22,3,7,11,15,19,23};

void permutation_inverse(unsigned int message[24]){
    unsigned int save[24];
    for(int i=0;i<24;i++){
        save[i]=message[23-i]; /* save ← message */
    }
    for(int i=0;i<24;i++){
        message[permutation_tab_inverse[23-i]]=save[i];
    }
}

void sub_4bits_inverse(unsigned int message[4]){
    for(int i=0; i<16; i++){
        if (comparaison_tableaux(message,i) == 1){
            for(int j=0; j<4; j++){
                message[j]=boite_S_inverse[i][j];
            }
            break;
        }
    }
}

void substitution_inverse(unsigned int message[24]){
    unsigned int temp[4];
    for(int i=0;i<24;i++){
        for(int j=0;j<4;j++){
                temp[j]=message[i+j];/*separe message en 6 parts de 4 bits dans une variable temporaire*/
        }
        sub_4bits_inverse(temp);/*fais la substitution sur chaque var temporaire*/
        for(int j=0;j<4;j++){
                message[i+j]=temp[j];/*remplace les 4 bits substitués dans le message*/
        }
        i+=3;
    }
}

void dechiffrement(unsigned int message[24],CLES k){
    unsigned int etat[24];
    for(int i=0;i<24;i++){
        etat[i]=message[i]; /* Etat ← m */
    }
    for(int x=0;x<24;x++){ /*etat XOR K11*/
             etat[x]=etat[x] ^ k.K[10][x];/* Etat ← Etat ⊕ K11 */
        }    
    for(int i=1;i<=10;i++){ /* pour i = 1 jusqu’a 10 faire */
        permutation_inverse(etat);  /* Etat ← Permutation(Etat) */
        substitution_inverse(etat); /* Etat ← Substitution(Etat)*/
        for(int j=0;j<24;j++){
            etat[j]=etat[j] ^ k.K[10-i][j];/* Etat ← Etat ⊕ Ki*/
        }
    }
    for(int i=0;i<24;i++){
        message[i]=etat[i]; /*c(message) ← Etat */
    }
    /*retourne message*/
}