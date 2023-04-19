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


    int remove_accent(char dest[],const char src[]) {
        int i_dest = 0;

        for (int i_src = 0 ; src[i_src] != '\0' ; i_src++) {

            if ((src[i_src] >> 6) > 1) {
                printf("nul\n");
                // plus de 2 octets : caractère inconnu
                return -1;
            }
            else if (src[i_src] >> 7) {
                // 2 octets
                int n = valeur_scalaire(src + i_src++);
                char c;
                printf("%d",n);

                if ((224 <= n) && (n <= 229))      c = 'a';
                else if(231 == n) c = 'c';
                else if ((232 <= n) && (n <= 235)) c = 'e';
                else if ((236 <= n) && (n <= 239)) c = 'i';
                else if ((242 <= n) && (n <= 246)) c = 'o';
                else if ((249 <= n) && (n <= 252)) c = 'u';
                else if(255 == n) c='y';
                else if (339 == n){
                    dest[i_dest++] = 'o';
                    c = 'e';
                }

                else return -1;  // caractère inconnu

                dest[i_dest++] = c;
            }
            else {
                // un seul octet
                dest[i_dest++] = src[i_src];
            }
        }

        dest[i_dest] = '\0';
        return 0;
    }
