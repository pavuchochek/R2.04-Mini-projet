/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet :  3                                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé :  Chiffrement de messages    main                                *
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
*  Nom du fichier : main                                                      *
*                                                                             *
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*on immporte nos fonctions*/
#include "utils.h"
#include "chiffrement.h"


char choices[][23] = {"chiffrer un message", "déchiffrer un message",  "quitter le programme"};

void main() {
    printf("Bienvenue dans le programme de chiffrement de messages\n\n");
    printf("Que souhaitez-vous faire ?\n");
    printf("1 - Chiffrer un message\n");
    printf("2 - Déchiffrer un message\n");
    printf("3 - Quitter\n");

    printf("Votre choix : ");
    fflush(stdout);
    int choice_size;
    char *choice_input = user_input(&choice_size);
    while(check_key(choice_input) == 0){
        printf("Choix invalide, votre choix doit être un nombre\n");
        printf("Votre choix : ");
        fflush(stdout);
        choice_input = user_input(&choice_size);
    }

    int choice = atoi(choice_input);

    while(choice != 1 && choice != 2 && choice != 3){
        printf("Choix invalide, votre choix doit être 1, 2 ou 3\n");
        printf("Votre choix : ");
        fflush(stdout);
        choice_input = user_input(&choice_size);
        while(check_key(choice_input) == 0){
            printf("Choix invalide, votre choix doit être un nombre\n");
            printf("Votre choix : ");
            fflush(stdout);
            choice_input = user_input(&choice_size);
        }
        choice = atoi(choice_input);
    }
    printf("Vous avez choisi de %s\n\n", choices[choice -1]);

    if (choice == 3){
        return;
    }

    printf("Veuillez entrer votre message : \n");
    int input_size;
    char *input = user_input(&input_size);

    char msg_without_accent[input_size];
    remove_accent(msg_without_accent,input);
    int check_alpha = checkalpha(msg_without_accent);
        
    while(check_alpha == 0){
        printf("Le message contient des caractères non alphanumérique\n");
        printf("Veuillez entrer votre message : \n");
        input = user_input(&input_size);

        msg_without_accent[input_size];
        remove_accent(msg_without_accent,input);
        check_alpha = checkalpha(msg_without_accent);
    }

    int key_size;
    printf("Veuillez saisir votre clé : ");
    fflush(stdout);
    char *key_input =user_input(&key_size);
    while(check_key(key_input) == 0){
        printf("Clé invalide, votre clé doit être un nombre\n");
        printf("Veuillez saisir votre clé : ");
        fflush(stdout);
        key_input = user_input(&key_size);

    }
    int key = atoi(key_input);

    char final_message[input_size];
    char *result;
    if (choice == 1){
        result = ChiffrementCesar(final_message, msg_without_accent, key);
    }
    else{
        result = DechiffrementCesar(final_message, msg_without_accent, key);
    }
    printf("Votre message final est : %s\n", result);
    return;
}
    
