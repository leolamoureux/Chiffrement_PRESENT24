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
    int m1=0x094f4b8;
    int c1=0x0bbd3cb;
    attaque(m1,c1);
    int res=double_chiffrement(m1,5841527,5855507);
    printf("res=%x\n",res);
//5841527
//5855507
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps pour l'attaque = %f\n", temps);
/*_____________________________________________________________________*/

    return 0;
}