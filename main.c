#include "PRESENT24.h"
#include "attaque.h"

int  main (int argc, char *argv[]) {
/*________________________________________CHIFFREMENT_____________________________________*/
    printf("----------------------------\n");
    printf("message = %s\n",argv[1]);
    printf("clé = %s\n",argv[2]);
    unsigned int message[24];
    unsigned int cle[24];
    hexa_to_bits(argv[1],message);
    hexa_to_bits(argv[2],cle);
    char *message_chiffre=malloc(6*sizeof(char));
    CLES k=cadencement(cle);/*algorithme de cadencement qui donne 11 clés de 24bits en sortie*/
    chiffrement(message,k);/*on chiffre le message avec les 11 clés*/
    bits_to_hexa(message,message_chiffre);/*on convertit ce message en bits en un message en hexa*/
    printf("=\n");
    printf("message chiffré = %s\n",message_chiffre);
    printf("----------------------------\n");
/*___________________________________________________________________________________________*/


/*_______________________________________DECHIFFREMENT______________________________________________*/
    char *message_dechiffre_hexa=malloc(6*sizeof(char));
    dechiffrement(message,k);
    bits_to_hexa(message,message_dechiffre_hexa);/*on convertit ce message en bits en un message en hexa*/
    printf("=\n");
    printf("message déchiffré = %s\n",message_dechiffre_hexa);
    printf("----------------------------\n");
/*__________________________________________________________________________________________________*/

/*___________________________________ATTAQUE PAR LE MILIEU___________________________________________*/
    unsigned int message_clair[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned int message_c[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    comparaison_listes(message_clair,message_c);
/*__________________________________________________________________________________________________*/

    return 0;
}