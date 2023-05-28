/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet :  3                                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé :   Chiffrement Cesar et dechiffrement                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 :  Sofia Gribanova                                             *
*                                                                             *
*  Nom-prénom2 :  Simon Armand                                                *
*                                                                             *
*  Nom-prénom3 :  Christian Gikapa                                            *
*                                                                             *
*  Nom-prénom4 :  Dorian Levasseur                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier :     chiffrement                                           *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*Tout d'abord ont défini notre chiffrement principal qui prend en entrée un tableau de caractères, une clé et une table de caractères qui sera le résultat*/
char * ChiffrementCesar(char dest[],char phrase[],int cle){
    /*On défini un caractère avec lequel on va parcourir chaque lettre de la phrase*/
    char c;
    int i;
    /*Une boucle qui parcourt toute la phrase*/
    for (i=0; phrase[i]!='\0'; i++){
        
        /*On ne chiffre pas les espaces.*/
        if (phrase[i] == ' '){
            dest[i] = ' ';
        }

        /*Sinon si c'est une lettre, on peut le chiffrer*/
        else if(isalnum(phrase[i]) != 0){

            /*c devient donc le char de la phrase parcouru.*/
            c = phrase[i];

            /* si c'est compris, entre a et z*/
            if (c >= 'a' && c <= 'z') {
                /*On effectue les calculs nécessaires:
                on ajoute la clé, 
                en ajoutant 26 pour éviter de sortir de l'intervalle*/
                c = c - 'a';
                c += cle;
                c = (c+26) % 26;
                c = c + 'a';
            } else if (c >= 'A' && c <= 'Z') {
                /* On effectue les mêmes opérations si c'est des majuscules.*/
                c = c - 'A';
                c += cle;
                c = (c+26) % 26;
                c = c + 'A';
            }
            dest[i] = c;
        }else{
            /*Si même après le traitement des caractères spéciaux quelque chose ne va pas, on sort une erreur en disant qu'il y a un mauvais char.*/
            printf("Mauvais char %c \n", phrase[i]);
        }
    }
    dest[i] = '\0';
    return dest;
}

/*Le déchiffrement consiste tout simplement à effectuer un chiffrement avec une clé négative.*/
char * DechiffrementCesar(char dest[],char phrase[],int cle){
    return ChiffrementCesar(dest,phrase, -cle);
}
