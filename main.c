#include "PRESENT24.h"

int  main (int argc, char *argv[]) {
    unsigned int message[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned int cle[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    CLES k=cadencement(cle);
    chiffrement(message,k);
    /////////////les 11 clés en bits///////////////////////
    for(int i=0;i<11;i++){
        printf("k=");
        for(int j=0;j<24;j++){
            printf("%d",k.K[i][j]);
        }
        printf("\n");
    }
    ////////////////////////////////////////////////
        printf("message chiffré = ");
        for(int j=0;j<24;j++){
            printf("%d",message[j]);
        }
        printf("\n");

    return 0;
}