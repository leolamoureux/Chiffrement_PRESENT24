# include  <stdlib.h>
# include  <stdio.h>
# include  <string.h>


////////////////Listes des fonctions////////////////

char *chiffrement(char *message, char *cle);
char *cadencement(char *cle);
char *substitution(char *message);
char *permutation(char *message);
char  XOR(int a, int b);

/*conversions*/
char *hexa_vers_bits(char *string); /*convertir un message en hexadécimal en un message en bits*/
char *bits_vers_hexa(char *string); /* convertir un message en bits en un message en hexadécimal*/
