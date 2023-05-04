#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


char* getText()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool done = SDL_FALSE;
    static char text[256] = "";
    int textLength = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return NULL;
    }

    if (TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur TTF_Init : %s", TTF_GetError());
        SDL_Quit();
        return NULL;
    }

    window = SDL_CreateWindow("Saisie de texte", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    TTF_Font *font = TTF_OpenFont("font/Lato-Black.ttf", 24);
    if (font == NULL){
        fprintf(stderr, "Erreur de font %s \n", TTF_GetError());
    }

    SDL_Color color = { 0, 0, 0, 255 };

    while (!done)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);

            switch (event.type)
            {
            case SDL_QUIT:
                done = SDL_TRUE;
                break;
            case SDL_TEXTINPUT:
                strcat(text, event.text.text);
                textLength++;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    printf("Texte saisi : %s\n", text);
                    //strcpy(text, "");
                    textLength = 0;
                    return text;

                }
                break;
            default:
                break;
            }
        }

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect = { 5, 212, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_Quit();
    SDL_Quit();
    /*
    if (textLength > 0) {
            return strdup(text);
        }else{
            return NULL;
        }*/

    return text;
}

int main(int argc, char *argv[])
{
    char* txt = getText();
    printf("Texte renvoyé : %s\n", txt);
    return EXIT_SUCCESS;
}
