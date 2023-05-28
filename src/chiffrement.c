/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet :  3                                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé :   Chiffrement Cesar et dechiffrement                                                              *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 :  Sofia Gribanova                                                    *
*                                                                             *
*  Nom-prénom2 :  Simon Armand                                                           *
*                                                                             *
*  Nom-prénom3 :  Christian Gikapa                                                         *
*                                                                             *
*  Nom-prénom4 :  Dorian Levasseur                                                       *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier :     chiffrement                                                     *
*                                                                             *
******************************************************************************/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*Tout d'abord on defini notre chiffrement principal qui prend en entrée un tableau de caracteres,une clé et une table de caracteres qui sera le resultat*/
char * ChiffrementCesar(char dest[],char phrase[],int cle){
    /*on defini un caractere avec lequel on va parcourir chaque lettre de la phrase*/
    char c;
    int i;
    /*une boucle qui parcourt tout la phrase*/
    for (i=0; phrase[i]!='\0'; i++){
        
        /*on ne chiffre pas les espaces*/
        if (phrase[i] == ' '){
            dest[i] = ' ';
        }

        /*si non si c'est une lettre on peut le chiffrer*/
        else if(isalnum(phrase[i]) != 0){

            /*car. c devient donc le car. de la phrase parcouru*/
            c = phrase[i];

            /* et si le c est contenu entre a et z*/
            if (c >= 'a' && c <= 'z') {
                /*on effectue les calculs necessaires:
                on ajoute la clé, 
                en ajoutant 26 pour eviter de sortir de l'intervalle*/
                c = c - 'a';
                c += cle;
                c = (c+26) % 26;
                c = c + 'a';
            } else if (c >= 'A' && c <= 'Z') {
                /* on effectue les memes operations si c'est des majuscules*/
                c = c - 'A';
                c += cle;
                c = (c+26) % 26;
                c = c + 'A';
            }
            dest[i] = c;
        }else{
            /*si meme apres le traitement des caracteres speciaux quelquechose ne va pas  on sort une erreur en disant qu'il y a un mauvais car.*/
            printf("Mauvais char %c \n", phrase[i]);
        }
    }
    dest[i] = '\0';
    return dest;
}
/*le dechiffrement consiste tout simplement a effectuer un chiffrement avec une clé negative*/
char * DechiffrementCesar(char dest[],char phrase[],int cle){
    return ChiffrementCesar(dest,phrase, -cle);
}
