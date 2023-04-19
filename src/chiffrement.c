#include <stdio.h>
#include <string.h>

char* ChiffrementCesar(char phrase[],int cle){
    char element = phrase[0];
    char new_phrase[] = phrase ;
    int i = 0;
    while (element != '\0') {
        if (element >= 'a' && element <= 'z') {
            element = element - 'a';
            element += cle;
            element = (element+26) % 26;
            element = element + 'a';
        } else if (element >= 'A' && element <= 'Z') {
            element = element - 'A';
            element += cle;
            element = (element+26) % 26;
            element = element + 'A';
        }
        new_phrase[i] = element;
        i++;
        element = phrase[i];
    }
    return new_phrase;
}

char* DechiffrementCesar(char phrase[],int cle){
    return ChiffrementCesar(phrase, -cle);
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

int main() {
    char str[] = "Tais-toi mec !";
    
    char *code = ChiffrementCesar(str, 10);
    printf("%s\n", str);
    //printf("%s\n", DechiffrementCesar(str, 10));
    Ecriture(str,code);
    return 0;
}