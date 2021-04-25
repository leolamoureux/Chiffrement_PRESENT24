#include "PRESENT24.h"

int  main (int argc, char *argv[]) {

    //printf("message : %s, clé : %s\n",argv[1],argv[2]);
    char *message="000000";
    char *cle="000000";
    CLES k=cadencement(cle);
    message = chiffrement(message,k);
    printf("message chiffré = %s\n",message);

    return 0;
}