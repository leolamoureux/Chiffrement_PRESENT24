#include "present.h"
#include <stdint.h>
/*dictionnaires utilisés pour les opérations*/
static const int sbox[16]={0x0c, 0x05, 0x06, 0x0b, 0x09, 0x00, 
                            0x0a, 0x0d, 0x03, 0x0e, 0x0f, 0x08, 
                            0x04, 0x07, 0x01, 0x02 };

static const int pbox[24]={0,6,12,18,1,7,13,19,2,8,14,20,3,9,15,21,4,10,16,22,5,11,17,23};

/*fonction pour convertir une chaine de caractère représentant un entier en hexadécimal, en un entier en décimal*/
int hexa_to_dec(char *mot){
    int x=0;
    for(int i=strlen(mot)-1;i>=0;i--){
        if (mot[i]>='0' && mot[i]<='9'){x=x+((mot[i]-48)*pow(16,strlen(mot)-1-i));}
        if (mot[i]>='a' && mot[i]<='f'){x=x+((mot[i]-87)*pow(16,strlen(mot)-1-i));}
    }
    return x;
}

int substitution(int etat){
    int tmp,tmp2;
    tmp = sbox[etat & 15];
    tmp2 = (sbox[(etat >> 4) & 15]) << 4; 
    tmp = tmp | tmp2; 
    tmp2 = (sbox[(etat >> 8) & 15]) << 8; 
    tmp = tmp | tmp2;
    tmp2 = (sbox[(etat >> 12) & 15]) << 12; 
    tmp = tmp | tmp2;
    tmp2 = (sbox[(etat >> 16) & 15]) << 16; 
    tmp = tmp | tmp2;
    tmp2 = (sbox[(etat >> 20) & 15]) << 20; 
    tmp = tmp | tmp2;
    etat = tmp;
    return etat;
}


int permutation(int etat){
    int tmp, tmp2, decalage; 
    tmp = etat & 1; 
    for(int i=1; i<24; i++){ 
        double p = pow(2,i);
        int res = (int) p;  
        tmp2 = etat & res; 
        decalage = i - pbox[i]; 
        if(decalage > 0) tmp2 = tmp2 >> decalage; 
        if(decalage < 0) tmp2 = tmp2 << -(decalage); 
        tmp = tmp | tmp2; 
    }
    etat = tmp;
    return etat;
}


CLES cadencement(int cle_maitre){
    uint64_t partie_haute=0;/*stockage des 64 bits les plus a gauche de la clé de 80 bits*/
    uint64_t partie_basse=0;/*stockage des 16 bits les plus a droite de la clé de 80 bits*/
    uint64_t temp=0;/*variable tampon pour les opérations de pivot*/
    uint64_t temp_box=0;/*variable tempon pour les opération avec la sbox*/
    CLES cles;/*structure pour stocker les 11 clés*/

    partie_haute |= ((uint64_t)cle_maitre) << 40;/*on met les 24 bits de la clé maitre tout a gauche de la clé de 80bits*/

    for(int i=0;i<11;i++){

        /*constitution de la clé avec les bits 39....16*/
        cles.K[i]=partie_haute & 0x0ffffff;
        
        /*on décale de 61 positions vers la gauche*/
        temp = partie_haute;
        temp = (temp << 61)|(temp >> (64 - 61));
        partie_haute = (partie_haute << 16)|(partie_haute >> (64 - 16));
        partie_haute &= 0xffffffffffff0000;
        partie_haute |= partie_basse;
        partie_haute = partie_haute << 45;  
        partie_basse = 0;
        partie_haute &= 0xffffe00000000000;
        partie_basse |= temp;
        temp = temp >> 16;
        temp &= 0x00001fffffffffff;
        partie_haute |= temp;
        
        /*on sauvegarde dans temp les 4 bits les plus a gauche passés dans la sbox*/
        temp_box = sbox[(partie_haute >> 60) & 0x0f];
        
        /*on remplace dans la partie haute*/
        partie_haute = (partie_haute & 0x0fffffffffffffff) | ( temp_box << 60);
       
        /*xor des bits 19 18 17 16 15 avec i*/
        partie_haute ^= ((uint64_t)(i+1) >> 1);
        partie_basse ^= ((uint16_t)(i+1) << 15);
    }
    return cles;
}

/*fonctio de chiffrement selon l'algorithme donné*/
int chiffrement(int message_clair,CLES cles){
    int etat=message_clair;

    for(int i=1;i<=10;i++){
        etat ^= cles.K[i-1]; /*Etat ← Etat ⊕ Ki*/
        etat=substitution(etat);/*Etat ← Substitution(Etat)*/
        etat=permutation(etat);/*Etat ← Permutation(Etat)*/
    }
    etat ^= cles.K[10];/*Etat ← Etat ⊕ K11*/
    return etat;
}



