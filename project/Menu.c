//Menu functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include "headers.h"

int show_menu(SDL_Renderer * sdlrenderer, SDL_Rect* r1, SDL_Rect* r2, SDL_Rect* r3)
{   
    SDL_bool shallExit = SDL_FALSE;
    mouse mouse;
    while(shallExit == SDL_FALSE)
    {
        SDL_SetRenderDrawColor(sdlrenderer, 0xe0, 0xe0, 0xe0, 0xff);
        SDL_RenderClear(sdlrenderer);
        SDL_SetRenderDrawColor(sdlrenderer, 0x33, 0x00, 0x66, 0xff);
        SDL_RenderFillRect(sdlrenderer, r1);
        SDL_RenderFillRect(sdlrenderer, r2);
        SDL_RenderFillRect(sdlrenderer, r3);
        menutext(sdlrenderer, r1, r2, r3);

        SDL_RenderPresent(sdlrenderer);
        SDL_Delay(1000/60);
        SDL_Event sdlEvent;

        while(SDL_PollEvent(&sdlEvent))
        {
            switch(sdlEvent.type)
            {
                case SDL_QUIT:
                shallExit = SDL_TRUE;
                break;
               
                case SDL_MOUSEBUTTONDOWN:
                mouse.x = sdlEvent.button.x;
                mouse.y = sdlEvent.button.y;
                int a = validate(r1, r2, r3, &mouse);
                return a;
                break;
               
            }
        }
   }
   return 0;
}
void menubuttons (SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3)
{
    rect1->x = 600;
    rect1->y = 300;
    rect1->h = 150;
    rect1->w = 300;
    rect2->x = 600;
    rect2->y = 700;
    rect2->w = 300;
    rect2->h = 150;
    rect3->x = 600;
    rect3->y = 1100;
    rect3->w = 300;
    rect3->h = 150;
}
int validate (SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3, mouse* mouse)
{
    if (mouse->x >= rect1->x && mouse->x < (rect1->x + rect1->w) && 
        mouse->y >= rect1->y && mouse->y < (rect1->y + rect1->h) )
        return 1;
    else if (mouse->x >= rect2->x && mouse->x < (rect2->x + rect2->w) && 
             mouse->y >= rect2->y && mouse->y < (rect2->y + rect2->h))
        return 2;
    else if (mouse->x >= rect3->x && mouse->x < (rect3->x + rect3->w) && 
             mouse->y >= rect3->y && mouse->y < (rect3->y + rect3->h))
        return 3;
    else 
        return -1; 
}
void menutext (SDL_Renderer* renderer, SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3)
{
    if (TTF_Init() != 0)
    {
        printf("%s", TTF_GetError());
    }
    TTF_Font *sans = TTF_OpenFont("Sans.ttf", 25);
    if(!sans) 
    {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    SDL_Surface* surface;
    SDL_Texture* texture;
    rect1->h = 140; rect1->w = 290; rect1->x = 605; rect1->y = 305;
    rect2->h = 140; rect2->w = 290; rect2->x = 605; rect2->y = 705;
    rect3->h = 140; rect3->w = 290; rect3->x = 605; rect3->y = 1105;
    SDL_Color white = {255, 255, 255, 255};
    surface = TTF_RenderText_Solid(sans, "New Game", white);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect1);
    surface = TTF_RenderText_Solid(sans, "Resume game", white);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect2);
    surface = TTF_RenderText_Solid(sans, "View rankings", white);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect3);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(sans);
    TTF_Quit(); 
}
