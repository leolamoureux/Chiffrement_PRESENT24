#include "attaque.h"
#include "PRESENT24.h"
/*2^24=16777216*/


ListeM init_M(){
    ListeM LM;
    LM.message_clair=malloc(16777216*sizeof(int));
    LM.cle==malloc(16777216*sizeof(int));
    return LM;
}

ListeC init_C(){
    ListeC LC;
    LC.message_chiffre=malloc(16777216*sizeof(int));
    LC.cle==malloc(16777216*sizeof(int));
    return LC;
}

ListeM remplir_liste_M(){
    ListeM LM=init_M();

    return LM;
}
ListeC remplir_liste_C(){
    ListeC LC=init_C();

    return LC;
}