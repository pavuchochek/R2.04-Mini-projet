//importation des bibliothèques nécessaires
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h> // SDL va permettre la création de l'interface
#include <SDL2/SDL_ttf.h> // TTF va permettre l'écriture dans l'interface

// definition des constantes de la taille de la fenetre
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//définition de la structure appData pour organiser les variables entre les fonctions
typedef struct {
    SDL_Window* window; // fenetre
    SDL_Renderer* renderer; // contenu de la fenetre
    int textWidth; // largeur du texte saisi 
    int textHeight; // longueur du texte saisi
    SDL_bool done; // booléen pour lancer la réception des actions sur la fenetre
    char text[256]; // tableau de char pour stocker la saisie
    int textLength; // taille du tableau pour les calculs liés à l'affichage
    TTF_Font* font; // déclaration de la police d'écriture
    char key[256]; // tableau pour la saisie de la clé
    int keyNumber; // convertion du tableau en integer
} AppData;

void initialize(AppData* appData) {
    appData->done = SDL_FALSE;
    appData->textLength = 0;

    //initialisation de la fenetre

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        exit(1);
    }

    //initialisation de la police 

    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur TTF_Init : %s", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    //création de la fenetre

    appData->window = SDL_CreateWindow("Chiffrement de César", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (appData->window == NULL) {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    //création du contenu de la fenetre (un rectangle blanc)

    appData->renderer = SDL_CreateRenderer(appData->window, -1, 0);
    SDL_SetRenderDrawColor(appData->renderer, 255, 255, 255, 255);
    SDL_RenderClear(appData->renderer);
    SDL_RenderPresent(appData->renderer);

    SDL_SetRenderDrawColor(appData->renderer, 0, 0, 0, 150);
    SDL_RenderFillRect(appData->renderer, NULL);
    SDL_SetRenderTarget(appData->renderer, NULL);
}

// fonction de nettoyage de la mémoire

void cleanup(AppData* appData) {
    SDL_DestroyRenderer(appData->renderer);
    SDL_DestroyWindow(appData->window);
    TTF_Quit();
    SDL_Quit();
}

// fonction d'écriture dans la fenetre

void renderText(AppData* appData, TTF_Font* font, const char* text, int x, int y) {
    
    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(appData->renderer, surface);

    SDL_QueryTexture(texture, NULL, NULL, &(appData->textWidth), &(appData->textHeight));

    SDL_Rect textRect = { x, y, appData->textWidth, appData->textHeight };

    SDL_RenderCopy(appData->renderer, texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// affichage du menu dans la fenetre 

void render(AppData* appData) {
    int c = 0;
    TTF_Font* font = TTF_OpenFont("font/Lato-Black.ttf", 36);
    if (font == NULL) {
        fprintf(stderr, "Erreur de font %s \n", TTF_GetError());
    }

    SDL_SetRenderDrawColor(appData->renderer, 255, 255, 255, 255);
    SDL_RenderClear(appData->renderer);

    renderText(appData, font, " ", 0, 0);
    renderText(appData, font, "Veuillez saisir un message", (120 -(appData->textWidth) / 2), (180 - (appData->textHeight) / 2 - 150));
    renderText(appData, font, "Votre message :", (390 - (appData->textWidth) / 2), (235 - (appData->textHeight) / 2 - 150));
    renderText(appData, font, "Votre message code :", (270 - (appData->textWidth) / 2), (350 - (appData->textHeight) / 2 - 150));

    TTF_Font* font2 = TTF_OpenFont("font/Lato-BlackItalic.ttf", 24);
    renderText(appData, font2, "Cle : ", (200 - (appData->textWidth) / 2), (300 - (appData->textHeight) / 2));

    while(c!= 1){

        SDL_RenderPresent(appData->renderer);
        c++;
    }

}

// affichage de la saisie utilisateur

void renderTextInput(AppData* appData, TTF_Font* font) {
    
    SDL_SetRenderDrawColor(appData->renderer, 255, 255, 255, 255);

    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended(font, appData->text, color);

    int textWidth = surface->w;
    int textHeight = surface->h;

    int rectWidth = textWidth + 40;
    int rectHeight = textHeight + 30;

    rectWidth = (rectWidth > 640) ? 640 : rectWidth;
    rectHeight = (rectHeight > 480) ? 480 : rectHeight;
    
    int rectX = (640 - rectWidth) / 2;
    int rectY = 280 - (textHeight / 2) - 150;
    
    SDL_Rect textRect = { rectX, rectY, rectWidth, rectHeight };
    
    SDL_RenderDrawRect(appData->renderer, &textRect);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(appData->renderer, surface);
    SDL_RenderCopy(appData->renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// fonction d'écriture de la clé dans la fenetre  

void renderKeyInput(AppData* appData, TTF_Font* font) {
    
    SDL_SetRenderDrawColor(appData->renderer, 255, 255, 255, 255);

    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended(font, appData->text, color);

    int textWidth = surface->w;
    int textHeight = surface->h;

    int rectWidth = textWidth + 40;
    int rectHeight = textHeight + 30;

    rectWidth = (rectWidth > 640) ? 640 : rectWidth;
    rectHeight = (rectHeight > 480) ? 480 : rectHeight;

    int rectX = (640 - rectWidth) / 2;
    int rectY = 280 - (textHeight / 2) - 150;
    
    SDL_Rect textRect = { rectX, rectY, rectWidth, rectHeight };
    
    SDL_RenderDrawRect(appData->renderer, &textRect);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(appData->renderer, surface);
    SDL_RenderCopy(appData->renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// affichage de la saisie dans la fenetre

void saisie(AppData* appData){

    TTF_Font* font = TTF_OpenFont("font/Lato-Regular.ttf", 36);

    if (font == NULL) {

        fprintf(stderr, "Erreur de font %s \n", TTF_GetError());
    }

    render(appData);

    for (int i = 0; i < appData->textLength; ++i) {
        renderTextInput(appData, font);
        SDL_RenderPresent(appData->renderer);
    }

    TTF_CloseFont(font);
}

// attente de la saisie utilisateur

int count =0; // pour permettre de changer de champ entre le message a coder et la clé 

void handleEvents(AppData* appData) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (count == 0){
            switch (event.type) {
                case SDL_QUIT:
                    appData->done = SDL_TRUE;
                    break;
                case SDL_TEXTINPUT:
                    strcat(appData->text, event.text.text);
                    appData->textLength++;
                    printf("Texte saisi : %s\n", appData->text);
                    saisie(appData);
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        printf("Texte saisi : %s\n", appData->text);
                        appData->textLength = 0;
                        count++;
                        printf("count : %d\n", count);
                        break; 
                    }
                    break;
                default:
                    break;
            }
        } else {
                switch (event.type) {
                case SDL_QUIT:
                    appData->done = SDL_TRUE;
                    break;
                case SDL_TEXTINPUT:
                    strcat(appData->key, event.text.text);
                    //appData->textLength++;
                    printf("clé : %s\n", appData->key);
                    saisie(appData);
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        appData->keyNumber = atoi(appData->key);
                        printf("clé saisie : %d\n", appData->keyNumber);
                        res(appData);
                        SDL_Delay(500);
                        appData->done=SDL_TRUE;
                        break;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

//affichage et stockage du message saisi 

char* getText(AppData* appData) {

    initialize(appData);
    printf("Veuillez saisir un texte à coder svp\n");

    SDL_StartTextInput();

    render(appData);

    while (!appData->done) {
        handleEvents(appData);
    }

    SDL_StopTextInput();

    cleanup(appData);

    char* text = malloc((appData->textLength + 1) * sizeof(char));
    strcpy(text, appData->text);

    return text;
}

//affichage de la clé saisie

void res (AppData* appData){

    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur TTF_Init : %s", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    TTF_Font* font = TTF_OpenFont("font/Lato-Black.ttf", 24);
    if (font == NULL) {
        fprintf(stderr, "Erreur de font %s \n", TTF_GetError());
    }

    renderText(appData, font, " ", 0, 0);
    renderText(appData, font, appData->key, (80 - (appData->textWidth) / 2), (295 - (appData->textHeight) / 2));
    SDL_RenderPresent(appData->renderer);

}
//affichage du message codé
/*
void output (AppData* appData){

    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur TTF_Init : %s", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    TTF_Font* font = TTF_OpenFont("font/Lato-Black.ttf", 36);
    if (font == NULL) {
        fprintf(stderr, "Erreur de font %s \n", TTF_GetError());
    }

    renderText(appData, font, " ", 0, 0);
    renderText(appData, font, out, (200 - (appData->textWidth) / 2), (300 - (appData->textHeight) / 2));
    SDL_RenderPresent(appData->renderer);

}
*/

int main(int argc, char* argv[]) {
    AppData appData;
    char* txt = getText(&appData);
    printf("Texte renvoyé : %s\n", txt);
    printf("Clé renvoyée : %d\n", appData.keyNumber);
    //char out[];
    //ChiffrementCesar(out,txt,keyNumber);
    cleanup(appData);
    return EXIT_SUCCESS;
}
