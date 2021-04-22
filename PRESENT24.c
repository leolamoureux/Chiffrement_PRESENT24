#include "PRESENT24.h"

////////////dictionnaire bits et hexadécimal////////////////

char *dico_bits[16]={"0000","0001","0010","0011",
    "0100","0101","0110","0111","1000","1001","1010",
    "1011","1100","1101","1110","1111"};

char dico_hexa[16]={'0','1','2','3','4','5',
                    '6','7','8','9',
                    'a','b','c','d','e','f'};
////////////////////////////////////////////////////////////


char *hexa_vers_bits(char *string){

    char *new=malloc(24*sizeof(char));
    
    for(int i=0;i<6;i++){
        for(int j=0;j<16;j++){
             if (string[i]==dico_hexa[j]) strcat(new,dico_bits[j]);
        }
    }

    return new;
}

char *bits_vers_hexa(char *string){
    char *new=malloc(6*sizeof(char));
    char temp[4];
    int cmpt=0;
    for(int i=0;i<6;i++){
        for(int j=cmpt;j<cmpt+4;j++){
             temp[j-cmpt]=string[j];
        }
        for(int x=0;x<16;x++){
            if (strcmp(temp,dico_bits[x])==0) new[i]=dico_hexa[x];
        }

        cmpt+=4;
    }

    return new;
}


char XOR(int a, int b){

    int c = a ^ b;
    char d;
    if (c==0)d='0';
    if (c==0)d='1';
    return d;
}

char *chiffrement(char *message, char *cle){
    

    return message;
}

char *substitution(char *message){

    return message;
}

char *permutation(char *message){

    /* on convertit le message en suite de bits*/
    message=hexa_vers_bits(message);

    /*tableau des permutations*/
    int permutation[24]={0,6,12,18,1,7,13,19,2,8,14,20,3,9,15,21,4,10,16,22,5,11,17,23};
    char temp[24];
    /*on charge la chaine de caractère message dans le tableau de caractère temp*/
    for (int i=0;i<24;i++){
        temp[i]=message[i]; 
    }
    /*on permute dans le tableau temp*/
    for (int i=0;i<24;i++){
        temp[i]=temp[permutation[i]];
    }
    /*la chaine de caractère message prend les valeur du tableau temp*/
    message=temp;

    /*on reconvertit le message en hexa*/
    message=bits_vers_hexa(message);
    return message;
}
