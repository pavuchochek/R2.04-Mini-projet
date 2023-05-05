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
    static char stars[256] = "";
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

    window = SDL_CreateWindow("Chiffrement de César", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN); 
                                                                                                     //(bug) SDL_WINDOW_RESIZABLE

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

    TTF_Font *font = TTF_OpenFont("font/Lato-Black.ttf", 36);
    if (font == NULL){
        fprintf(stderr, "Erreur de font %s \n", TTF_GetError());
    }

    SDL_Color color = { 0, 0, 0, 255 };

    printf("Veuillez saisir un texte à coder svp\n");

    // AFFICHAGE MESSAGE CACHE
    SDL_Surface *surface4 = TTF_RenderText_Blended(font, "votre message : ", color);
    SDL_Texture *texture4 = SDL_CreateTextureFromSurface(renderer, surface4);
    
    int textWidth, textHeight;
    SDL_QueryTexture(texture4, NULL, NULL, &textWidth, &textHeight);
    
    SDL_Rect textRect4 = { (640 - textWidth) / 2, (480 - textHeight) / 2-50, textWidth, textHeight };
    
    SDL_RenderCopy(renderer, texture4, NULL, &textRect4);
    
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture4);
    SDL_FreeSurface(surface4);
    //------------------------------------------

    // AFFICHAGE MESSAGE CODE    
    SDL_Surface *surface2 = TTF_RenderText_Blended(font, "votre message code : ", color);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    
    SDL_QueryTexture(texture2, NULL, NULL, &textWidth, &textHeight);
    
    SDL_Rect textRect2 = { (640 - textWidth) / 2, (480 - textHeight) / 2+50, textWidth, textHeight };
    
    SDL_RenderCopy(renderer, texture2, NULL, &textRect2);
    
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(surface2);
    //----------------------------------------------------

    // AFFICHAGE CLE
    TTF_Font *font2 = TTF_OpenFont("font/Lato-BlackItalic.ttf", 24);

    SDL_Surface *surface3 = TTF_RenderText_Blended(font2, "Cle : 10", color);
    SDL_Texture *texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
    
    SDL_QueryTexture(texture3, NULL, NULL, &textWidth, &textHeight);
    
    SDL_Rect textRect3 = { (640 - textWidth) / 2-230, (480 - textHeight) / 2-46, textWidth, textHeight };
    
    SDL_RenderCopy(renderer, texture3, NULL, &textRect3);
    
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture3);
    SDL_FreeSurface(surface3);
    //--------------------------------------------
    
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
                for (int i; i<textLength; i++){
                    stars[i]='*';
                    printf("Taille de stars actuelle : %d\n", i);
                }

                TTF_Font *font = TTF_OpenFont("font/Lato-Black.ttf", 36);

                SDL_Surface *surface = TTF_RenderText_Blended(font, stars, color); 
                //"text" à la place de "stars" pour afficher le message (bug)
                
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                
                int textWidth, textHeight;
                SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
                
                SDL_Rect textRect = { (640 - textWidth) / 2, (480 - textHeight) / 2, textWidth, textHeight };
                
                SDL_RenderCopy(renderer, texture, NULL, &textRect);
                
                SDL_RenderPresent(renderer);

                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);

                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    printf("Texte saisi : %s\n", text);
                    printf("Taille de 'text' : %d\n", textLength);
                    textLength = 0;
                    done = SDL_TRUE;
                    break;
                }
                break;
            default:
                break;
            }
        }

    SDL_Delay(3000);

    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();

    return text;
}

int main(int argc, char *argv[])
{
    char* txt = getText();
    //ChiffrementCesar(txt,10);
    printf("Texte renvoyé : %s\n", txt);
    return EXIT_SUCCESS;
}
