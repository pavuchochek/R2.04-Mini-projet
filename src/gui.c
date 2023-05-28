#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int textWidth;
    int textHeight;
    SDL_bool done;
    char text[256];
    int textLength;
    char stars[256];
    TTF_Font* font;
} AppData;

void initialize(AppData* appData) {
    appData->done = SDL_FALSE;
    appData->textLength = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur TTF_Init : %s", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    appData->window = SDL_CreateWindow("Chiffrement de César", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (appData->window == NULL) {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    appData->renderer = SDL_CreateRenderer(appData->window, -1, 0);
    SDL_SetRenderDrawColor(appData->renderer, 255, 255, 255, 255);
    SDL_RenderClear(appData->renderer);
    SDL_RenderPresent(appData->renderer);

    SDL_SetRenderDrawColor(appData->renderer, 0, 0, 0, 150);
    SDL_RenderFillRect(appData->renderer, NULL);
    SDL_SetRenderTarget(appData->renderer, NULL);
}

void cleanup(AppData* appData) {
    SDL_DestroyRenderer(appData->renderer);
    SDL_DestroyWindow(appData->window);
    TTF_Quit();
    SDL_Quit();
}

void renderText(AppData* appData, TTF_Font* font, const char* text, int x, int y) {
    SDL_Surface* picture=NULL;
    SDL_Texture* pict=NULL;
    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(appData->renderer, surface);

    SDL_QueryTexture(texture, NULL, NULL, &(appData->textWidth), &(appData->textHeight));

    SDL_Rect textRect = { x, y, appData->textWidth, appData->textHeight };

    SDL_RenderCopy(appData->renderer, texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

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
    renderText(appData, font2, "Cle : 10", (200 - (appData->textWidth) / 2), (300 - (appData->textHeight) / 2));

    while(c!= 1){

        SDL_RenderPresent(appData->renderer);
        c++;
    }

}

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


void saisie(AppData* appData){

    TTF_Font* font = TTF_OpenFont("font/Lato-Black.ttf", 36);

    if (font == NULL) {

        fprintf(stderr, "Erreur de font %s \n", TTF_GetError());
    }

    render(appData);

    for (int i = 0; i < appData->textLength; ++i) {
        renderTextInput(appData, font);
        SDL_RenderPresent(appData->renderer);
        //SDL_RenderClear(appData->renderer);
    }

    TTF_CloseFont(font);
}

void handleEvents(AppData* appData) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
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
                    appData->done = SDL_TRUE;
                    break;
                }
                break;
            default:
                break;
        }
    }
}


char* getText() {
    AppData appData;
    TTF_Font* font;

    initialize(&appData);

    font = TTF_OpenFont("font/Lato-Black.ttf", 36);
    if (font == NULL) {
        fprintf(stderr, "Erreur de font %s \n", TTF_GetError());
    }

    printf("Veuillez saisir un texte à coder svp\n");

    SDL_StartTextInput();

    render(&appData);

    while (!appData.done) {
        handleEvents(&appData);
    }

    SDL_StopTextInput();

    cleanup(&appData);

    char* text = malloc((appData.textLength + 1) * sizeof(char));
    strcpy(text, appData.text);

    return text;
}


int main(int argc, char* argv[]) {
    char* txt = getText();
    printf("Texte renvoyé : %s\n", txt);
    return EXIT_SUCCESS;
}
