#include <stdio.h>
#include <stddef.h>
#include <locale.h>
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

unsigned int ord(const char str[2]){
    wchar_t ws[2];
    mbstowcs(ws, str, 2);
    return ws[0];
}

int remove_accent(char dest[],const char src[]) {
    

    int i_dest = 0;
    if (setlocale(LC_CTYPE, "") == NULL)
	{
		perror("setlocale");
		return EXIT_FAILURE;
	}

    for (int i_src = 0 ; src[i_src] != '\0' ; i_src++) {
        

        if ((src[i_src] >> 6) > 1) {
            // plus de 2 octets : caractère inconnu
            return -1;
        }
        if (src[i_src] >> 7) {
            // 2 octets
            unsigned int n = ord(src + i_src++);
            char c;

            if (198 == n){
                dest[i_dest++] = 'A';
                c = 'E';
            }
            else if(199 == n) c = 'C';
            else if ((192<=n) && (n<=196)) c='A';
            else if ((200<=n) && (n<=203)) c='E';
            else if ((206==n) || (n==207)) c='I';
            else if ((212==n) || (n==214)) c='O';
            else if ((217<=n) && (n<=220)) c='U';
            else if ((224 <= n) && (n <= 229)) c = 'a';
            else if (230 == n){
                dest[i_dest++] = 'a';
                c = 'e';
            }
            else if(231 == n) c = 'c';
            else if ((232 <= n) && (n <= 235)) c = 'e';
            else if ((236 <= n) && (n <= 239)) c = 'i';
            else if ((242 <= n) && (n <= 246)) c = 'o';
            else if ((249 <= n) && (n <= 252)) c = 'u';
            else if ((255==n)) c='y';
            else if (338 == n){
                dest[i_dest++] = 'O';
                c = 'E';
            }
            else if (339 == n){
                dest[i_dest++] = 'o';
                c = 'e';
            }
            else if ((376==n)) c='Y';
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
