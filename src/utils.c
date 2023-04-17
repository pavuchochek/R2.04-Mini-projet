#include <stdio.h>
#include <stdlib.h>

#define BUFFER 512

char * user_input(int *input_size) {
    
    char * input = malloc(sizeof(char) * BUFFER);
    *input_size = 0;  // IL FAUT INITIALISER SA MERE LA PUTE

    // saisie
    input[0] = getchar();
    while (input[*input_size] != '\n') {
        if (!(++(*input_size) % BUFFER)) {
            // l'entrée dépasse la taille de la chaîne donc ajout d'espace
            input = realloc(input, sizeof(char) * (*input_size + BUFFER));
        }
        input[*input_size] = getchar();
    }

    // ajout de l'octet nul
    input[(*input_size)++] = '\0';
    // ajustement de la taille du pointeur au texte
    //input = realloc(input, sizeof(char) * (*input_size));

    return input;
}

int valeur_scalaire(const char str[2]) {
    unsigned char c1 = str[0] << 6;  // premier octet (tête)
    unsigned char c2 = (unsigned char) (str[1] << 2) >> 2;  // deuxième octet (fin)
    return c1 + c2;
}
