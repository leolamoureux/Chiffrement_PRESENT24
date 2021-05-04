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
    /*      couples pour l'attaque de Léo Lamoureux :

    (m1,c1) = (c92a8e, 49e0f7)---(m2,c2) = (f1f410,391c18)
    
    couples LOLA :

    (m1,c1) = (94f4b8, bbd3cb) (m2,c2) = (111ef1,8773b3) */

    int m1=0x094f4b8;       int m2=0x0111ef1;
    int c1=0x0bbd3cb;       int c2=0x08773b3;

    printf("attaque (m1=%x,c1=%x / m2=%x,c2=%x) : \n",m1,c1,m2,c2);
    attaque(m1,c1,m2,c2);

    t2=clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps total pour l'attaque = %f s\n", temps);
    printf("\n");
/*_____________________________________________________________________*/

    return 0;
}