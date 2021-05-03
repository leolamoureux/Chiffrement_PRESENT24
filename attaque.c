#include "attaque.h"
#include "present.h"
#include <stdint.h>
#include <time.h>

#define TAILLE 16777216


void remplir_liste_M(int message_clair, int *liste){
    for(int i=0;i<TAILLE;i++){
        CLES K=cadencement(i);/*cadencement avec la clé = l'iteration i*/
        liste[i]=chiffrement(message_clair,K);/*resultat du chiffrement stocké dans la liste M*/
        liste[i]=liste[i]<<24 | i;
    }
}

void remplir_liste_C(int message_chiffre,int *liste){
    for(int i=0;i<TAILLE;i++){
        CLES K=cadencement(i);/*cadencement avec la clé = l'iteration i*/
        liste[i]=dechiffrement(message_chiffre,K);/*resultat du dechiffrement stocké dans la liste C*/
        liste[i]=liste[i]<<24 | i;
    }
}

void tri_rapide (int *tableau, int taille) {
    int mur, courant, pivot, tmp;
    if (taille < 2) return;
    // On prend comme pivot l element le plus a droite
    pivot = tableau[taille - 1];
    mur  = courant = 0;
    while (courant<taille) {
        if (tableau[courant] <= pivot) {
            if (mur != courant) {
                tmp=tableau[courant];
                tableau[courant]=tableau[mur];
                tableau[mur]=tmp;              
            }
            mur ++;
        }
        courant ++;
    }
    tri_rapide(tableau, mur - 1);
    tri_rapide(tableau + mur - 1, taille - mur + 1);
}

void compare_tab(int *tab1, int *tab2,int *liste_indices,int taille){
    for(int i=0;i<taille;i++){
        if((tab1[i] & 0xffffff000000) == (tab2[i] & 0xffffff000000))liste_indices[i]=0;
        else liste_indices[i]=1;
    }
}

int double_chiffrement(int message_clair,int cle1,int cle2){
    CLES K1=cadencement(cle1);
    CLES K2=cadencement(cle2);
    int message_chiffre=chiffrement(message_clair,K1);
    message_chiffre=chiffrement(message_chiffre,K2);
    return message_chiffre;
}

void attaque(int message_clair,int message_chiffre){

/*________CREATION_DES_LISTES________________*/
    int *Liste_M=malloc(TAILLE*sizeof(unsigned long));
    int *Liste_C=malloc(TAILLE*sizeof(unsigned long));

    remplir_liste_M(message_clair,Liste_M);
    remplir_liste_C(message_chiffre,Liste_C);
/*_____________________________________________*/

/*____________TRI_DES_LISTES____________________*/
    tri_rapide(Liste_M,TAILLE);
    tri_rapide(Liste_C,TAILLE);
/*_______________________________________________*/

/*____________ELEMENTS_COMMUNS_________________________*/
    int *liste_indices=malloc(TAILLE*sizeof(int));
    compare_tab(Liste_M,Liste_C,liste_indices,TAILLE);
    int cle_1,cle_2;
    int resultat;
    for(int i=0;i<TAILLE;i++){
        if(liste_indices[i]==0){
            cle_1=Liste_M[i] & 0x0ffffff;
            cle_2=Liste_C[i] & 0x0ffffff;
            resultat=double_chiffrement(message_clair,cle_1,cle_2);
            if(resultat==message_chiffre){
                printf("clé 1 = %x, clé 2 = %x\n",cle_1,cle_2);
                printf("resultat=%x\n",resultat);
                return;
            }
        }

    }
/*____________________________________________________*/
}