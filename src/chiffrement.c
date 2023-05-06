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

int Ecriture(char org[],char str[]){
	//printf("%s\n", org);
	//printf("%s\n", str);
	FILE* fichier;
	fichier = fopen("f1.txt", "a+");
	if(fichier == NULL){
		printf("Erreur a l'ouverture du fichier f1\n");
	} else{
		printf("Ouverture du fichier f1 reussie\n");
		
		fprintf(fichier,"message original : \n");
		fprintf(fichier,"%s \n", org);
		fprintf(fichier,"message codé : \n");
		fprintf(fichier, "%s \n", str);
		fclose(fichier);
	}
	return 0;
}
