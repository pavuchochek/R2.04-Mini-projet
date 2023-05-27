#include <stdio.h>
#include <string.h>
#include <ctype.h>

char * ChiffrementCesar(char dest[],char phrase[],int cle){
    char c;
    for (int i=0; phrase[i]!='\0'; i++){
        if (phrase[i] == ' '){
            dest[i] = ' ';
        }else if(isalnum(phrase[i]) != 0){
            c = phrase[i];
            if (c >= 'a' && c <= 'z') {
                c = c - 'a';
                c += cle;
                c = (c+26) % 26;
                c = c + 'a';
            } else if (c >= 'A' && c <= 'Z') {
                c = c - 'A';
                c += cle;
                c = (c+26) % 26;
                c = c + 'A';
            }
            dest[i] = c;
        }else{
            printf("Mauvais char %c \n", phrase[i]);
        }
    }
    return dest;
}

char * DechiffrementCesar(char dest[],char phrase[],int cle){
    return ChiffrementCesar(dest,phrase, -cle);
}
