#include "PRESENT24.h"
///////__________________dictionnaires__________________________///////////

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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////_____________________________CHIFFREMENT_______________________________________________///////////////////////////////////////////////

void permutation(unsigned int message[24]){
    unsigned int save[24];
    for(int i=0;i<24;i++){
        save[i]=message[23-i]; /* save ← message */
    }
    for(int i=0;i<24;i++){
        message[permutation_tab[23-i]]=save[i];
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

void rotation(unsigned int tab[80]){
    int i, tmp = tab[79];
    for(i=79;i>0;i--){
        tab[i] = tab[i - 1];
    }
    tab[0] = tmp;
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
        unsigned int save[80]; 
        for(int i=0;i<80;i++){
            save[i]=regTemp[i];/* on sauvegardera le registre dans save */
        }
        /*pivot*/
        for(int i=0;i<61;i++){
            rotation(regTemp);/*61 décalage de 1 position*/
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
        unsigned int tour_en_bits[5];
        for(int i=1;i<5;i++){tour_en_bits[i]=bits_tab[tour][i-1];}/*on convertit la valeur du tour en bits*/
        tour_en_bits[0]=0;/*le premier bit à 0*/
        for(int i=19;i>=15;i--){
            regTemp[i]=regTemp[i] ^ tour_en_bits[19-i];/*XOR bit à bit*/
        }
        //////////////////////////////////////////////////////////////////////
    }
//////////////////////////////////////////////////////////////////////////////
    return cles;
}

void chiffrement(unsigned int message[24],CLES k){
    unsigned int etat[24];
    for(int i=0;i<24;i++){
        etat[i]=message[i]; /* Etat ← m */
    }
    for(int i=1;i<=10;i++){ /* pour i = 1 jusqu’a 10 faire */
        for(int j=0;j<24;j++){
            etat[j]=etat[j] ^ k.K[i-1][j];/* Etat ← Etat ⊕ Ki*/
        }
        substitution(etat); /* Etat ← Substitution(Etat)*/
        permutation(etat);  /* Etat ← Permutation(Etat) */
    }
    for(int x=0;x<24;x++){ /*etat XOR K11*/
             etat[x]=etat[x] ^ k.K[10][x];/* Etat ← Etat ⊕ K11 */
        }
    
    for(int i=0;i<24;i++){
        message[i]=etat[i]; /*c(message) ← Etat */
    }
    /*retourne message*/
}
//////////////////////////////////////////////////////////////////////////////////

///////_______________________________CONVERSION______________________________/////////////////////////
void bits_to_hexa(unsigned int message[24]){

}
void hexa_to_bits(char *mot_hexa,unsigned int message_destination[24]){
    int tab[6];
    for(int i=0;i<6;i++){/*on convertit les caractères en entiers qu'on place dans tab*/
        if(mot_hexa[i]>=97){tab[i]=mot_hexa[i]-87;}/*si c'est une lettre*/
        else{tab[i]=mot_hexa[i]-48;}/*si c'est un chiffre entre 0 et 9*/
    }
    for(int i=0;i<6;i++){
        for(int j=4*i;j<(4*i+4);j++){
            message_destination[j]=bits_tab[tab[i]][j-(i*4)];
        }
    }
    

}
//////////////////////////////////////////////////////////////////////////