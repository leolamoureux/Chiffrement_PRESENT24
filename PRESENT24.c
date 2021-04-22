#include "PRESENT24.h"

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
    return message;
}
