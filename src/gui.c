#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int textWidth;
    int textHeight;
    SDL_bool done;
    char text[256];
    int textLength;
    char stars[256];
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

    // design (patouch)

    picture = SDL_LoadBMP("font/sunshine.png");
    pict = SDL_CreateTextureFromSurface(renderer,picture);
    SDL_FreeSurface(picture);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void render(AppData* appData) {
    TTF_Font* font = TTF_OpenFont("font/Lato-Black.ttf", 36);
    if (font == NULL) {
        fprintf(stderr, "Erreur de font %s \n", TTF_GetError());
    }

    SDL_SetRenderDrawColor(appData->renderer, 255, 255, 255, 255);
    SDL_RenderClear(appData->renderer);

    renderText(appData, font, " ", 0, 0);
    renderText(appData, font, "Veuillez saisir un message", (120 -(appData->textWidth) / 2), (250 - (appData->textHeight) / 2 - 150));
    renderText(appData, font, "Votre message :", (390 - (appData->textWidth) / 2), (250 - (appData->textHeight) / 2 - 50));
    renderText(appData, font, "Votre message code :", (270 - (appData->textWidth) / 2), (240 - (appData->textHeight) / 2 + 50));

    TTF_Font* font2 = TTF_OpenFont("font/Lato-BlackItalic.ttf", 24);
    renderText(appData, font2, "Cle : 10", (200 - (appData->textWidth) / 2), (300 - (appData->textHeight) / 2));

    SDL_RenderPresent(appData->renderer);

    TTF_CloseFont(font);
    TTF_CloseFont(font2);
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
                render(appData);
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
