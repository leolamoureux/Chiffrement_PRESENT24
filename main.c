#include "PRESENT24.h"

int  main (int argc, char *argv[]) {
/*________________________________________CHIFFREMENT_____________________________________*/
    printf("----------------------------\n");
    printf("message=%s\n",argv[1]);
    printf("clé=%s\n",argv[2]);
    unsigned int message[24];
    unsigned int cle[24];
    hexa_to_bits(argv[1],message);
    hexa_to_bits(argv[2],cle);
    char *message_chiffre=malloc(6*sizeof(char));
    CLES k=cadencement(cle);/*algorithme de cadencement qui donne 11 clés de 24bits en sortie*/
    chiffrement(message,k);/*on chiffre le message avec les 11 clés*/
    bits_to_hexa(message,message_chiffre);/*on convertit ce message en bits en un message en hexa*/
    printf("=\n");
    printf("message chiffré=%s\n",message_chiffre);
    printf("----------------------------\n");
/*___________________________________________________________________________________________*/


/*_______________________________________DECHIFFREMENT______________________________________________*/

/*__________________________________________________________________________________________________*/
    return 0;
}