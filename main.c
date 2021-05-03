#include "present.h"
#include "attaque.h"
#include <stdint.h>
#include <time.h>


int  main (int argc, char *argv[]) {
/*__________________INITIALISATION_______________________*/
    /*conversion*/
    int message_clair=hexa_to_dec(argv[1]);
    int cle_maitre=hexa_to_dec(argv[2]);

    /*cadencement*/
    CLES cles=cadencement(cle_maitre);
/*_______________________________________________________*/

/*____________________CHIFFREMENT_______________________*/
    int message_chiffre=chiffrement(message_clair,cles);
    printf("message chiffré = %x\n\n",message_chiffre);
/*______________________________________________________*/

/*____________________DECHIFFREMENT_______________________________*/
    int message_dechiffre=dechiffrement(message_chiffre,cles);
    printf("message déchiffré = %x\n",message_dechiffre);
    printf("---------------------\n");
/*________________________________________________________________*/


/*_____________________ATTAQUE_______________________________________*/
    float temps;
    clock_t t1, t2;
    t1 = clock();
    int *Liste_M=malloc(16777216*sizeof(int));
    int *Liste_C=malloc(16777216*sizeof(int));

    remplir_liste_M(message_clair,Liste_M);
    remplir_liste_C(message_chiffre,Liste_C);

    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps pour remplir les listes = %f\n", temps);
/*_____________________________________________________________________*/

    return 0;
}