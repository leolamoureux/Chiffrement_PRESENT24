#include "present.h"

/*fonctions de déchiffrement*/
int substitution_inverse(int etat);
int permutation_inverse(int etat);
int dechiffrement(int message, CLES cles);