#include "PRESENT24.h"

int  main (int argc, char *argv[]) {

    //printf("message : %s, clé : %s\n",argv[1],argv[2]);

    char *message="f955b9";
    char *message2 = cadencement(message);
    printf("message2= %s\n",message2);

    return 0;
}