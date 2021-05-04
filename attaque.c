#include "attaque.h"
#include "present.h"
#include <stdint.h>
#include <time.h>

#define TAILLE 16


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








/*fonction de tri rapide*/
// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 

int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
 
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
void tri_rapide(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}









void compare_tab(unsigned long long *tab1, unsigned long long *tab2,int *liste_indices,int taille){
    float temps;
    clock_t t1, t2;
    t1=clock();
    int nb_elements=0;
    for(int i=0;i<taille;i++){ 
            if((tab1[i] & 0xffffff000000) == (tab2[i] & 0xffffff000000)){
                int j=i;
                while(((tab1[i] & 0xffffff000000) == (tab2[j-1] & 0xffffff000000))){
                    
                    j--;
                }
                liste_indices[i]=((tab1[i] & 0x0ffffff) << 24) | (tab2[i] & 0x0ffffff);
                nb_elements += 1;
                }
            else liste_indices[i]=1;
        }
    t2=clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps pour comparaison = %f s\n", temps);
    printf("nombre elements communs = %d\n",nb_elements);
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
    tri_rapide(Liste_M,1,TAILLE);
    tri_rapide(Liste_C,1,TAILLE);

    t3=clock();
    temps = (float)(t3-t2)/CLOCKS_PER_SEC;
    printf("temps pour le tri rapide = %f s\n", temps);
/*_______________________________________________*/

/*____________ELEMENTS_COMMUNS_________________________*/
    int *liste_indices=malloc(TAILLE*sizeof(int));
    /*on compare les tableaux triés*/
    compare_tab(Liste_M,Liste_C,liste_indices,TAILLE);
    int cle_1,cle_2;
    int resultat1,resultat2;
    /*pour chaque élément commun, on effectue le double chiffrement avec ses clés k1 et k2*/
    for(int i=0;i<TAILLE;i++){
        if(liste_indices[i]!=1){
            cle_1=(liste_indices[i] & 0xffffff000000)>>24;
            cle_2=liste_indices[i] & 0x0ffffff;
            resultat1=double_chiffrement(m1,cle_1,cle_2);
            resultat2=double_chiffrement(m2,cle_1,cle_2);
            /*si les resultats obtenus sont égaux aux messages chiffrés,
              alors c'est que les clés a l'iteration i sont les bonnes*/
            if(resultat1==c1 && resultat2==c2){
                /*on les affiches, ainsi que le resultat*/
                printf("clé 1 = %x, clé 2 = %x\n",cle_1,cle_2);
                printf("resultat 1 =%x, resultat 2 = %x\n",resultat1,resultat2);
                t4=clock();
                temps = (float)(t4-t3)/CLOCKS_PER_SEC;
                printf("temps pour trouver les clés = %f s\n", temps);
                return;
            }
        }

    }
/*____________________________________________________*/
}