# include  <stdlib.h>
# include  <stdio.h>
# include  <string.h>
#include "PRESENT24.h"

void dechiffrement(unsigned int message[24],CLES k);
void sub_4bits_inverse(unsigned int message[4]);
void substitution_inverse(unsigned int message[24]);