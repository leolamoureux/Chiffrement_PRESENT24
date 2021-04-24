#include "PRESENT24.h"

/////////////////////dictionnaires//////////////////////////

char *dico_bits[16]={"0000","0001","0010","0011",
    "0100","0101","0110","0111","1000","1001","1010",
    "1011","1100","1101","1110","1111"};

char dico_hexa[16]={'0','1','2','3','4','5',
                    '6','7','8','9',
                    'a','b','c','d','e','f'};

char boite_s[16]={'c','5','6','b','9','0',
                    'a','d','3','e',
                    'f','8','4','7','1','2'};
////////////////////////////////////////////////////////////


char *hexa_vers_bits(char *string){

    char *new=malloc(24*sizeof(char));
    
    for(int i=0;i<strlen(string);i++){
        for(int j=0;j<16;j++){
             if (string[i]==dico_hexa[j]) strcat(new,dico_bits[j]);
        }
    }

    return new;
}

char *bits_vers_hexa(char *string){
    char *new=malloc(6*sizeof(char));
    char temp[4];
    int cmpt=0;
    for(int i=0;i<strlen(string);i++){
        for(int j=cmpt;j<cmpt+4;j++){
             temp[j-cmpt]=string[j];
        }
        for(int x=0;x<16;x++){
            if (strcmp(temp,dico_bits[x])==0) new[i]=dico_hexa[x];
        }

        cmpt+=4;
    }

    return new;
}


char XOR(int a, int b){

    int c = a ^ b;
    char d;
    if (c==0)d='0';
    if (c==1)d='1';
    return d;
}


char *substitution(char *message){

    char temp[16];

    for (int i=0;i<strlen(message);i++){
        temp[i]=message[i]; 
    }

    for(int j=0;j<strlen(message);j++){
        for (int i=0;i<16;i++){
            if(message[j]==dico_hexa[i])temp[j]=boite_s[i];
        }
    }

    message=temp;
    return message;
}

char *permutation(char *message){

    /* on convertit le message en suite de bits*/
    message=hexa_vers_bits(message);

    /*tableau des permutations*/
    int permutation[24]={0,6,12,18,1,7,13,19,2,8,14,20,3,9,15,21,4,10,16,22,5,11,17,23};
    char temp[strlen(message)];
    /*on charge la chaine de caractère message dans le tableau de caractère temp*/
    for (int i=0;i<strlen(message);i++){
        temp[i]=message[i]; 
    }
    /*on permute dans le tableau temp*/
    for (int i=0;i<strlen(message);i++){
        temp[i]=temp[permutation[i]];
    }
    /*la chaine de caractère message prend les valeur du tableau temp*/
    message=temp;

    /*on reconvertit le message en hexa*/
    message=bits_vers_hexa(message);
    return message;
}

CLES cadencement(char *cle){

    char temp[80];/*registre temporaire = registre K */
    cle=hexa_vers_bits(cle);

    /*on met la clé en fin de chaine */
    strcat(temp,cle);

    /*on met les 56 bits restants à 0*/
    for(int i=strlen(cle);i<80;i++){strcat(temp,"0");}

    CLES k; /*structure qui contiendra les 11 sous-clés de 24 bits*/
    /*algo*/
    for(int tour=0;tour<11;tour++){
    /* constitution de la sous clé K[i] */
        for(int j=41;j<=64;j++){
           if(j==64){k.K[tour][j-40]='\0'; }
           k.K[tour][j-41]=temp[j];
        }
        /*étape 1 : pivot de 61 positions*/
        char save[strlen(temp)];
        /* on sauvegarde le registre dans save */
        for(int i=0;i<80;i++){
            save[i]=temp[i];
        }
        /*pivot*/
        for(int i=0;i<19;i++){
            temp[i+61]=temp[i];
        }
        for(int i=0;i<60;i++){
            temp[i]=save[i+20];
        }
        /*étape 2 : application boite_S aux 4 bits les plus a gauche*/
        char *sub=malloc(4*sizeof(char));
        for(int i=0;i<4;i++){
            sub[i]=temp[i];/*on met les 4 bits les plus a gauche dans une chaine temporaire*/
        }
        sub=bits_vers_hexa(sub);/*on convertit en hexadecimal*/
        sub=substitution(sub);/*on applique la substitution sur le code hexa*/
        sub=hexa_vers_bits(sub);/*on reconvertit en bit*/
        for(int i=0;i<4;i++){
            temp[i]=sub[i];/*on remplace les valeurs dans temp*/
        }
        /*étape 3: XOR*/
        char *d=dico_bits[tour];/*valeur du tour en bit pour le XOR*/
        for(int i=61;i<=65;i++){
            int a=(int)temp[i]-48;
            int b=(int)d[i-61]-48;
            temp[i]=XOR(a,b);/*a chaque iteration on XOR le bit de temp et le bit du tour actuel*/
        }
    }
    
    return k;
}

char *chiffrement(char *message, char *cle){


    return message;
}
