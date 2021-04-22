#include "PRESENT24.h"

int  main (int argc, char *argv[]) {

    printf("message : %s, clé : %s\n",argv[1],argv[2]);

    char *message="000001111122222333334444";
    char *message2 = permutation(message);
    printf("message2= %s\n",message2);

    
    return 0;
}