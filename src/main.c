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
#include "chiffrement.h"

void main() {

    //int input_size;
    //char *input = user_input(&input_size);
    //char msg[input_size] ;
    //remove_accent(msg,input);
    //printf("\n%s\n", msg);

    char msg[]= "abcd";
    int size_ =sizeof(msg)/sizeof(msg[0]);
    char dest[size_];
    int key = 1;
    char *res = ChiffrementCesar(dest,msg, key);
    printf("message: %s \nclé %d\ncodé: %s\n",msg,key,res );
}
