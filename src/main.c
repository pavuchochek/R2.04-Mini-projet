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

    char msg[]= "0BÉcdéàç";
    int size_ =sizeof(msg)/sizeof(msg[0]);
    char dest[size_];
    int rm_accent = remove_accent(dest,msg);
    int check_alpha = checkalpha(msg);
    if (check_alpha == 0)    {
        printf("Le message contient des caractères non alphabétiques\n");
    } 
    else    {
        printf("Le message ne contient pas de caractères non alphabétiques\n");
    }
    printf("%s\n%s\n",msg, dest);


}
    
