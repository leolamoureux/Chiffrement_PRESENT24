#include "attaque.h"
#include "present.h"
#include <stdint.h>
#include <time.h>

#define TAILLE 16777216


void remplir_liste_M(unsigned int message_clair, unsigned long long *liste){
    for(unsigned int i=0;i<TAILLE;i++){
        CLES K=cadencement(i);/*cadencement avec la clé = l'iteration i*/
        liste[i]=chiffrement(message_clair,K);/*resultat du chiffrement stocké dans la liste M*/
        liste[i]=liste[i]<<24 | i;/*on stocke la clé dans le meme int mais sur les 24 bits de droite*/
    }
}

void remplir_liste_C(unsigned int message_chiffre, unsigned long long *liste){
    for(unsigned int i=0;i<TAILLE;i++){
        CLES K=cadencement(i);/*cadencement avec la clé = l'iteration i*/
        liste[i]=dechiffrement(message_chiffre,K);/*resultat du dechiffrement stocké dans la liste C*/
        liste[i]=liste[i]<<24 | i;/*on stocke la clé dans le meme int mais sur les 24 bits de droite*/
    }
}

/*fonctions de tri rapide*/
void quicksort(unsigned long long *number,int first,int last){
   int i, j, pivot;
   unsigned long long temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while((number[i] & 0x0ffffff000000)<=(number[pivot] & 0x0ffffff000000)&&i<last)
            i++;
         while((number[j] & 0x0ffffff000000)>(number[pivot] & 0x0ffffff000000))
            j--;
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);

   }
}

void compare_tab(unsigned long long *tab1, unsigned long long *tab2,unsigned int m1,unsigned int c1,unsigned int m2,unsigned int c2){
    int n1 = TAILLE;
    int message_obtenu1,message_obtenu2, clee1, clee2;
    int nb_elements=0;
  
    int  i = 0 ,  j = 0; 
  
    while((i < n1) && (j < n1)){
        
        if((tab1[i] & 0xffffff000000) < (tab2[j] & 0xffffff000000)) i++;
        else if((tab1[i] & 0xffffff000000) > (tab2[j] & 0xffffff000000)) j++;
        else{
            nb_elements +=1;
            clee1 = tab1[i] & 0x0ffffff;
            clee2 = tab2[j] & 0x0ffffff;
            message_obtenu1 = double_chiffrement(m1,clee1,clee2);
            message_obtenu2 = double_chiffrement(m2,clee1,clee2);
            if ((message_obtenu1 == c1) && (message_obtenu2 == c2)){
                printf("attaque réussie : \n");
                printf("nombre de collisions testées avant de trouver la bonne clée : %d\n",nb_elements);
                printf("clée k1 = %x, clée k2 = %x\n",clee1,clee2);
                return;
            }
            i++;
            j++;
        }   
    } 
}

unsigned int double_chiffrement(unsigned int message_clair,unsigned int cle1,unsigned int cle2){
    CLES K1=cadencement(cle1);/*cadencement pour la premiere clé*/
    CLES K2=cadencement(cle2);/*cadencement pour la 2ème clé*/
    unsigned int message_chiffre=chiffrement(message_clair,K1);/*1er chiffrement avec la 1ere clé*/
    message_chiffre=chiffrement(message_chiffre,K2);/*2eme chiffrement avec la 2eme clé*/
    return message_chiffre;/*on retourne le message chiffré 2 fois*/
}

void attaque(unsigned int m1,unsigned int c1,unsigned int m2,unsigned int c2){
    float temps;
    clock_t t1, t2, t3, t4, t5;
    t1 = clock();
/*________CREATION_DES_LISTES________________*/
    unsigned long long *Liste_M=malloc(TAILLE*sizeof(unsigned long long));
    unsigned long long *Liste_C=malloc(TAILLE*sizeof(unsigned long long));

    remplir_liste_M(m1,Liste_M);
    remplir_liste_C(c1,Liste_C);

    t2=clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps pour remplir les listes = %f s\n", temps);
/*__________________________________________________*/

/*____________TRI_DES_LISTES____________________*/
    quicksort(Liste_M,0,TAILLE-1);
    quicksort(Liste_C,0,TAILLE-1);

    t3=clock();
    temps = (float)(t3-t2)/CLOCKS_PER_SEC;
    printf("temps pour trier les listes = %f s\n", temps);
/*_______________________________________________*/

/*____________ELEMENTS_COMMUNS_________________________*/
    compare_tab(Liste_M,Liste_C,m1,c1,m2,c2);

    t4=clock();
    temps = (float)(t4-t3)/CLOCKS_PER_SEC;
    printf("temps pour trouver les clés = %f s\n", temps);
/*____________________________________________________*/
}