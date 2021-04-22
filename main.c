#include "PRESENT24.h"

int  main (int argc, char *argv[]) {

    printf("message : %s, clé : %s\n",argv[1],argv[2]);
    char *message;
    message = chiffrement(argv[1],argv[2]);
    return 0;
}