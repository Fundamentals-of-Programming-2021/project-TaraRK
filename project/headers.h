#ifndef __HEADERS_HEADER
#define __HEADERS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#define true 1;

typedef struct player
{
    char name[20];
   char whole_name[30];
   int score;
}player;

typedef struct dest 
{
    Sint16 x;
    Sint16 y;
}dest;

typedef struct soldier 
{
    Sint16 x;
    Sint16 y;
    Sint16 r;
    Uint32 color;
}soldier;

typedef struct triangle
{
    SDL_Point p1, p2, p3;
    SDL_Point center;
    int soldiernum;
    int attacksoldiernum;
    Uint32 background;
    SDL_Rect number;
    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;
    char numstr [5];
    long long int counter;
    int flag;
    soldier* soldiers;
    int attack;
} triangle;

typedef struct opponent
{
    int opattacksoldiernum;
}opponent;

typedef struct potion
{
    SDL_Rect rect;
    SDL_Rect textbox;
    int flag;
    int type;
    int counter;
    int countmax;
    SDL_Rect time;
    int stopattack;
    int r;
    int rp;
    int rgameprogress;
    int attack;
    int activeforopp;
} potion;

typedef struct mouse
{
    int x;
    int y;
    int src;
    int dest;
} mouse;

//Map fuctions
void inttostr(int a, char* b);
void textgenerator(triangle* triangles, SDL_Renderer* renderer, int n);
int timestamp (SDL_Event* event);
void initialize1(triangle* triangles);
void initialize2(triangle* triangles);
void initialize3(triangle* triangles);
void centercalculator(triangle* triangles, int n);
void drawcastle (triangle* triangles, int n, SDL_Renderer* renderer);
void rectinitializer (triangle* triangles, int n);
void drawmap(triangle* triangles, SDL_Renderer* renderer);
int choosemap(SDL_Renderer * sdlrenderer);
void uploadimage(SDL_Renderer* renderer, char* name, int x, int y);
// Menu Functions
void menubuttons (SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3);
int validate (SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3, mouse* mouse);
void menutext (SDL_Renderer* renderer, SDL_Rect* rect1, SDL_Rect* rect2, SDL_Rect* rect3);
int show_menu(SDL_Renderer * sdlrenderer, SDL_Rect* r1, SDL_Rect* r2, SDL_Rect* r3);
void swap(player *xp, player *yp);
void bubbleSort(player participants[], int n);
void uploadimage(SDL_Renderer* renderer, char* name, int x, int y);
int whichmap(mouse* mouse);
//Game fuctions
int maingame(int map);
int sourcefinder (triangle* triangles, int n, SDL_Event* event, mouse* Mouse);
int destfinder (triangle* triangles, int n, SDL_Event* event, mouse* Mouse);
void gameprogress (triangle* triangles, int n, int a, int flag);
int oppinit(triangle* triangles,int n, int* opsrc, int* opdest, potion* potion);

//Potion functions
void potionrenderer (potion* potion, SDL_Renderer* sdlRenderer);
void createpotion (potion* potion);
int hitpotion (soldier* soldiers, potion* potion);
void potiontime(SDL_Renderer* renderer, potion* potion);
void potiontext(potion* potion, SDL_Renderer* renderer);
void potionquit (potion* potion);
void potioninit(potion* potion);
// Scoarboard Functions
void textmaker(SDL_Renderer *renderer, int x, int y, char *text);
void getusername(SDL_Renderer * renderer, char* username);
void sortusernames(char *new_username, player* participants, int n);
void load_image(SDL_Renderer * sdlRenderer,char * string,int x0,int y0,int w0,int h0);
void rankings(SDL_Renderer * sdlRenderer,const int SCREEN_WIDTH,const int SCREEN_HEIGHT);

#endif