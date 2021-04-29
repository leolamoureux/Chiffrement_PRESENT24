#include "PRESENT24.h"
#include "attaque.h"
#include <time.h>

int  main (int argc, char *argv[]) {
/*___________________________________TEMPS EXECUTION_________________________________________*/
    float temps;
    clock_t t1, t2;


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
    t1 = clock();
    ListeM LM=remplir_liste_M(message_clair);
    ListeC LC=remplir_liste_C(message_c);
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps pour remplir les listes = %f\n", temps);
/*__________________________________________________________________________________________________*/

    return 0;
}