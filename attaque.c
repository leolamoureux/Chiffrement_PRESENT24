#include "attaque.h"
#include "PRESENT24.h"
/*2^24=16777216*/
void comparaison_listes(unsigned int message_clair[24], unsigned int message_chiffre[24]){
    unsigned int tab_i[24],tab_j[24],iter_i,iter_j;
    for(int i=0;i<5;i++){

        /*conversion de i en binaire*/
        iter_i=i;
        for(int x=0;iter_i>0;x++){  
            tab_i[23-x]=iter_i%2;  
            iter_i=iter_i/2; 
        }
        /*on met tous les autres bits non utilisés à 0*/
        for(int a=0;a<24;a++){
            if(tab_i[a]!=1)tab_i[a]=0;
        }
        /*on fait le cadencement pour chaque cle i = chaque valeur de tab de 0 à 2^24*/
        CLES K_i=cadencement(tab_i);
        chiffrement(message_clair,K_i);
        for(int j=0;j<5;j++){

            /*conversion de j en binaire*/
            iter_j=j;
            for(int x=0;iter_j>0;x++){  
                tab_j[23-x]=iter_j%2;  
                iter_j=iter_j/2; 
            }
            /*on met tous les autres bits non utilisés à 0*/
            for(int a=0;a<24;a++){
                if(tab_j[a]!=1)tab_j[a]=0;
            }
            /*on fait le cadencement pour chaque cle j*/
            CLES K_j=cadencement(tab_j);
            chiffrement(message_clair,K_j);
            
            /*comparaison messageclair(i) avec tous les message chiffrés*/
        }
    }
}
