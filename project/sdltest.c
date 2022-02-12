#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "headers.h"
#include "string.h"
#define true 1;

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 1500;
const int FPS = 55;
time_t t1;

int main(void)
{ 
    player* players = (player*)malloc(sizeof(player) * 10); 
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() != 0)
    {
        printf("%s", TTF_GetError());
    }
    TTF_Font *sans = TTF_OpenFont("Sans.ttf", 20);
   
    

    SDL_bool shallExit = SDL_FALSE;

    SDL_Window *sdlwindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, 
                                             SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlrenderer = SDL_CreateRenderer(sdlwindow, -1, 
                                                   SDL_RENDERER_PRESENTVSYNC | 
                                                   SDL_RENDERER_ACCELERATED);

    char username[20];
    char copy_username[20];
    strcpy(username," ");

    getusername(sdlrenderer, username);
    for(int i = 0; i < strlen(username);i++)
    {
      username[i] = username[i+1];
    }
    username[strlen(username)] = '\0';
    strcpy(copy_username,username);

    sortusernames(username,players,0);
    int number = -1;

    // SDL_bool button = SDL_FALSE;
    // SDL_Rect begingame;
    // SDL_Rect previousgame;
    // SDL_Rect Scoreboard;
    // menubuttons(&begingame, &previousgame, &Scoreboard);
    // while(number == -1)
    // {
    //   number = show_menu(sdlrenderer, &begingame, &previousgame, &Scoreboard);
    // }
    // printf("bus\n");
    // int a;
    // int begin = 0;
    // switch (number) 
    // {
    //     case 1 :
    //         a = choosemap(sdlrenderer);
    //         begin = 1;
    //         break;
    //     case 2 :
    //         //sorry 
    //         break;
    //     case 3 :
    //         rankings(sdlrenderer,SCREEN_WIDTH, SCREEN_WIDTH );
    //         break;

    // }
    int begin = 1;
    int state;
    if (begin)
    {
        state = maingame(1);
    }
    if (state == 1)
    {
        sortusernames(copy_username, players, 100);
        rankings(sdlrenderer,SCREEN_WIDTH, SCREEN_WIDTH );
    }
    else if (state == 2)
    {
        sortusernames(copy_username, players, -50);
        rankings(sdlrenderer,SCREEN_WIDTH, SCREEN_WIDTH );
    }

    
    SDL_DestroyRenderer(sdlrenderer);
    SDL_DestroyWindow(sdlwindow);

    SDL_DestroyRenderer(sdlrenderer);
    SDL_DestroyWindow(sdlwindow);
    TTF_CloseFont(sans);
    TTF_Quit();
    SDL_Quit();
}
