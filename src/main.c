/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet :  3                                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé :  Chiffrement de messages                                        *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 :  ARMAND Simon                                                *
*                                                                             *
*  Nom-prénom2 :  GIKAPA Christian                                            *
*                                                                             *
*  Nom-prénom3 :  GRIBANOVA Sofia                                             *
*                                                                             *
*  Nom-prénom4 :  LEVASSEUR Dorian                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier :                                                           *
*                                                                             *
******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "utils.h"

void main() {
    int input_size;
    char *input = user_input(&input_size);
    char msg[input_size] ;
    remove_accent(msg,input);
    
    //printf("Input %s\n\n", input);
    printf("\n\nInput sans accent %s\n", msg);
    //printf("entrée (taille = %d): \"%s\"\n", input_size, input);
    //
    //printf("Voilà la message: %s",message);
    /*
    for (i = 0; message[i] != '\0'; i++){
        message[i] = tolower((unsigned char) message[i]);
    }*/
    
}
