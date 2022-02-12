#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "headers.h"
//Potion Functions
SDL_Color black = {0, 0, 0, 255};
void potionrenderer (potion* potion, SDL_Renderer* sdlRenderer)
{
    if ( IMG_Init(IMG_INIT_JPG) != 0)
    {
        printf("%s", IMG_GetError());
    }
    SDL_Surface* surface;
    switch (potion->type)
    {
        case 1:
            surface = IMG_Load("1.jpg");
            break;
        case 2:
            surface = IMG_Load("2.jpg");
            break;
        case 3:
            surface = IMG_Load("3.jpg");
            break;
        case 4:
            surface = IMG_Load("4.jpg");
            break;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_RenderCopy(sdlRenderer, texture, NULL, &potion->rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    IMG_Quit();
}
void createpotion (potion* potion)
{
    if ( !(rand() % 60) )
    {
        int a = rand() % 4 + 1;
        potion->type = a;
        potion->flag = 0;
        switch (potion->type)
        {
            case 1 :
                potion->countmax = 300;
                potion->stopattack = 0;
                break;
            case 2 :
                potion->countmax = 500;
                break;
            case 3 :
                potion->countmax = 250;
                break;
            case 4 :
                potion->countmax = 400;
                break;
        }
        if ( !(rand() % 4) )
        {
            potion->rect.x = 300 + (rand() % 700);
            potion->rect.y = 400 + (rand() % 600);
        }
        else
        {
            potion->rect.x = 200 + (rand() % 300);
            potion->rect.y = 200 + (rand() % 300);
        }
        potion->rect.h = 50;
        potion->rect.w = 50;
    }    
}
void potiontest(potion* potion, SDL_Renderer* renderer)
{
    IMG_Init(IMG_INIT_JPG);
    SDL_Surface* surface = IMG_Load("/home/tara/Desktop/project/1.jpg");
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, text, NULL, &potion->rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(text);
    IMG_Quit();
}
int hitpotion (soldier* soldiers, potion* potion)
{
    if (soldiers->x >= potion->rect.x && (soldiers->x <= potion->rect.x + potion->rect.w) 
        && soldiers->y >= potion->rect.y && (soldiers->y <= potion->rect.y + potion->rect.h) )
        return 1;
    else 
        return 0;
}

void potiontime(SDL_Renderer* renderer, potion* potion)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x66, 0x33, 0xff);
    potion->time.x = 750;
    potion->time.y = 60;
    potion->time.h = 50;
    double temp = (double)(potion->counter) / (double)(potion->countmax);
    potion->time.w = temp * 600;
    SDL_RenderFillRect(renderer, &(potion->time));
    if (potion->type == 1)
    {
        potion->stopattack = 1;
    }    
}
void potioninit(potion* potion)
{
    switch (potion->type)
    {
        case 1 : // stops from moving
            potion->stopattack = 1;
            break;
        case 2 : // increases soldier speed
            if (potion->activeforopp) {potion->rp = 1.5;}
            else { potion->r = 1.5;}
            break;
        case 3 : //increases soldier creation rate
            potion->rgameprogress = 10;
            break;
        case 4 : // stops from attacking
            potion->attack = 0;
            break;

    }
}
// void potiontext (potion* potion, SDL_Renderer* renderer)
// {
//     sw
// }
void potionquit (potion* potion)
{
    switch (potion->type)
    {
        case 1 : // stops from moving
            potion->stopattack = 0;
            break;
        case 2 :
            potion->r = 1;
            potion->rp = 1;
            break;
        case 3 :
            potion->rgameprogress = 15;
            break;
        case 4 :
            potion->attack = 1;
            break;
    }
}
void potiontext(potion* potion, SDL_Renderer* renderer)
{
    SDL_Surface* surface;
    SDL_Texture* text;
    potion->textbox.x = 750;
    potion->textbox.y = 130;
    potion->textbox.h = 50;
    potion->textbox.w = 300;
    TTF_Font *sans = TTF_OpenFont("Sans.ttf", 20);
    if (potion->activeforopp)
    {
        switch (potion->type)
        {
            case 1:
                surface = TTF_RenderText_Solid(sans, "Movement block potion activated for opponent", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 2:
                surface = TTF_RenderText_Solid(sans, "Spead raise potion activated for opponent", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 3:
                surface = TTF_RenderText_Solid(sans, "Faster soldier creation activated for opponent", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 4:
                surface = TTF_RenderText_Solid(sans, "Attack block potion activated for opponent", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
        }
    }
    else 
    {
        switch (potion->type)
        {
            case 1:
                surface = TTF_RenderText_Solid(sans, "Movement block potion activated for player", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 2:
                surface = TTF_RenderText_Solid(sans, "Spead raise potion activated for player", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 3:
                surface = TTF_RenderText_Solid(sans, "Faster soldier creation activated for player", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 4:
                surface = TTF_RenderText_Solid(sans, "Attack block potion activated for player", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
        }
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(text);
    TTF_CloseFont(sans);
}
