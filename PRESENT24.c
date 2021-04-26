#include "PRESENT24.h"
////////////////////// dictionnaires //////////////////////////////
unsigned int bits_tab[16][4]={{0,0,0,0},//0
                              {0,0,0,1},//1
                              {0,0,1,0},//2
                              {0,0,1,1},//3
                              {0,1,0,0},//4
                              {0,1,0,1},//5
                              {0,1,1,0},//6
                              {0,1,1,1},//7
                              {1,0,0,0},//8
                              {1,0,0,1},//9
                              {1,0,1,0},//a
                              {1,0,1,1},//b
                              {1,1,0,0},//c
                              {1,1,0,1},//d
                              {1,1,1,0},//e
                              {1,1,1,1}};//f

unsigned int boite_S[16][4]={{1,1,0,0},//c
                             {0,1,0,1},//5
                             {0,1,1,0},//6
                             {1,0,1,1},//b
                             {1,0,0,1},//9
                             {0,0,0,0},//0
                             {1,0,1,0},//a
                             {1,1,0,1},//d
                             {0,0,1,1},//3
                             {1,1,1,0},//e
                             {1,1,1,1},//f
                             {1,0,0,0},//8
                             {0,1,0,0},//4
                             {0,1,1,1},//7
                             {0,0,0,1},//1
                             {0,0,1,0}};//2

int permutation_tab[24]={0,6,12,18,1,7,13,19,2,8,14,20,
                     3,9,15,21,4,10,16,22,5,11,17,23};
/////////////////////////////////////////////////////////////////////


void permutation(unsigned int message[24]){
    for(int i=0;i<24;i++){
        message[i]=message[permutation_tab[i]];
    }
}

int comparaison_tableaux(int tab[], int k){
    for(int i=0; i<4; i++) {
       if (tab[i]!=bits_tab[k][i]) return 0;
    }
     return 1;
}

void sub_4bits(unsigned int message[4]){
    for(int i=0; i<16; i++){
        if (comparaison_tableaux(message,i) == 1){
            for(int j=0; j<4; j++){
                message[j]=boite_S[i][j];
            }
            break;
        }
    }
}


void substitution(unsigned int message[24]){
    unsigned int temp[4];
    for(int i=0;i<24;i++){
        for(int j=0;j<4;j++){
                temp[j]=message[i+j];/*separe message en 6 parts de 4 bits dans une variable temporaire*/
        }
        sub_4bits(temp);/*fais la substitution sur chaque var temporaire*/
        for(int j=0;j<4;j++){
                message[i+j]=temp[j];/*remplace les 4 bits substitués dans le message*/
        }
        i+=3;
    }
}

CLES cadencement(unsigned int cle[24]){
    CLES cles;
    unsigned int regTemp[80];
    for(int i=79;i>=56;i--){
        regTemp[i]=cle[79-i];/*  la clé maître  est copiée dans les 24 bits de poids  */  
    }                        /*  fort du registre K                           */
    for(int i=55;i>=0;i--){
        regTemp[i]=0;     /*  les 56 bits restants initialisés à 0         */
    }
          /*ALGORITHME*/
//////////////////////////////*boucle des 11 clés*/////////////////////////////
    for(int tour=1;tour<=11;tour++){/* tours de l'algo                 */
        for(int i=39;i>=16;i--){
            cles.K[tour-1][39-i]=regTemp[i];/*  constitution de la sous clé Ki-1(de 0 à 10)  */
        }
        ///////////////////*étape 1 : pivot de 61 positions*///////////////////
        int save[80]; 
        for(int i=0;i<80;i++){
            save[i]=regTemp[i];/* on sauvegardera le registre dans save */
        }
        /*pivot*/
        for(int i=0;i<19;i++){
            regTemp[i+61]=regTemp[i];
        }
        for(int i=0;i<60;i++){
            regTemp[i]=save[i+20];
        }
        //////////////////////////////////////////////////////////////////////

        /////*étape 2 : application boite_S aux 4 bits les plus a gauche*/////
        int bits_4_gauche[4];
        for(int i=0;i<4;i++){
            bits_4_gauche[i]=regTemp[79-i];/* les 4 bits les plus a gauche stocké*/
        }                                  /* dans une var temporaire*/

        sub_4bits(bits_4_gauche);/* substitution */
    
        for(int i=0;i<4;i++){
            regTemp[79-i]=bits_4_gauche[i];/*on remplace les 4 bits dans le registre*/
        }
        //////////////////////////////////////////////////////////////////////

        ///////////////////////////*étape 3: XOR*/////////////////////////////
        unsigned int tour_en_bits[4];
        for(int i=0;i<4;i++){tour_en_bits[i]=bits_tab[tour][i];}/*on convertit la valeur du tour en bits*/
        for(int i=19;i>=15;i--){
            regTemp[i]=regTemp[i] ^ tour_en_bits[19-i];/*XOR bit à bit*/
        }
        //////////////////////////////////////////////////////////////////////
    }
//////////////////////////////////////////////////////////////////////////////
    return cles;
}

void chiffrement(unsigned int message[24],CLES k){
    for(int i=1;i<=10;i++){
        for(int j=0;j<24;j++){
            message[j]=message[j] ^ k.K[i][j];/*XOR bit à bit du message et de la clé Ki*/
        }
        substitution(message);
        permutation(message);
    }
    for(int x=0;x<24;x++){
             message[x]=message[x] ^ k.K[10][x];/*XOR bit à bit du message et de la clé Ki*/
        }
}