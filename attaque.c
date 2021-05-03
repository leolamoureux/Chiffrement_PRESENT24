#include "attaque.h"
#include "present.h"
#include <stdint.h>


void remplir_liste_M(int message_clair, int *liste){
    for(int i=0;i<16777216;i++){
        CLES K=cadencement(i);/*cadencement avec la clé = l'iteration i*/
        liste[i]=chiffrement(message_clair,K);/*resultat du chiffrement stocké dans la liste M*/
    }
}

void remplir_liste_C(int message_chiffre,int *liste){
    for(int i=0;i<16777216;i++){
        CLES K=cadencement(i);/*cadencement avec la clé = l'iteration i*/
        liste[i]=dechiffrement(message_chiffre,K);/*resultat du dechiffrement stocké dans la liste C*/
    }
}