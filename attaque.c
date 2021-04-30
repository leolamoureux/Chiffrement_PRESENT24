#include "attaque.h"
#include "PRESENT24.h"
/*2^24=16777216*/

ListeM init_M(){
    ListeM LM;
    LM.message=malloc(16777216*sizeof(int*));
    LM.cle=malloc(16777216*sizeof(int*));
    return LM;
}

ListeC init_C(){
    ListeC LC;
    LC.message=malloc(16777216*sizeof(int*));
    LC.cle=malloc(16777216*sizeof(int*));
    return LC;
}

ListeM remplir_liste_M(unsigned int message[24]){
    ListeM LM=init_M();
    unsigned int tab[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int iter;   
    for(int a=0;a<5;a++){
        iter=a;
        /*on convertit l'iteration en bits*/
        for(int i=0;iter>0;i++){  
           tab[23-i]=iter%2;  
           iter=iter/2;
        }
        LM.message[a]=message;
        LM.cle[a]=tab;/*clé stockée dans la liste M*/
        printf("\n");
        for(int i=0;i<24;i++){
            printf("%d",LM.cle[a][i]);
        }
        printf("\n");
        //CLES K=cadencement(LM.cle[a]);/*cadencement avec la clé a l'iteration a*/
       // chiffrement(LM.message[a],K);/*resultat du chiffrement stocké dans la liste M*/
    }
    return LM;
}
ListeC remplir_liste_C(unsigned int message[24]){
    ListeC LC=init_C();
    unsigned int tab[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int iter;   
    for(int a=0;a<30;a++){
        iter=a;
        /*on convertit l'iteration en bits*/
        for(int i=0;iter>0;i++){  
           tab[23-i]=iter%2;  
           iter=iter/2;
        }
        LC.message[a]=message;
        LC.cle[a]=tab;/*clé stockée dans la liste M*/
        CLES K=cadencement(LC.cle[a]);/*cadencement avec la clé a l'iteration a*/
        chiffrement(LC.message[a],K);/*resultat du chiffrement stocké dans la liste M*/
    }
    return LC;
}