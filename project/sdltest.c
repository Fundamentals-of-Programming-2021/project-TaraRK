#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <hi.h>
#define true 1;
const int FPS = 60;
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 1500;

SDL_Color black = {0, 0, 0, 255};

typedef struct mouse
{
    int x;
    int y;
    int src;
    int dest;
} mouse;
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
int sourcefinder (triangle* triangles, int n, SDL_Event* event)
{
    for (int i = 0; i < n; i++)
    {
        if ( ((event->button.x) - ((triangles + i)->center.x) ) * ((event->button.x) - ((triangles + i)->center.x) ) 
            +((event->button.y) - ((triangles + i)->center.y) ) * ((event->button.y) - ((triangles + i)->center.y) ) 
            <= 400 )
            {
                if ( (triangles + i)->flag )
                return i;
            }
    }
    return 0;
}

int destfinder (triangle* triangles, int n, SDL_Event* event)
{
    for (int i = 0; i < n; i++)
    {
        if ( ((event->button.x) - (triangles + i)->center.x ) * ((event->button.x) - (triangles + i)->center.x ) 
            +((event->button.y) - (triangles + i)->center.y ) * ((event->button.y) - (triangles + i)->center.y ) 
            <= 400 )
            {
                
                return i;
            }
    }
    return 0;
}



void textgenerator(triangle* triangles, SDL_Renderer* renderer, int n)
{
    TTF_Font *sans = TTF_OpenFont("/home/tara/Desktop/project/Sans.ttf", 20);
    for (int i = 0; i < n; i++)
    {
        inttostr((triangles + i)->soldiernum, (triangles + i)->numstr);
        (triangles + i)->surfaceMessage = TTF_RenderText_Solid(sans, (triangles + i)->numstr, black);
        (triangles + i)->Message = SDL_CreateTextureFromSurface(renderer, (triangles + i)->surfaceMessage);
        SDL_RenderCopy(renderer, (triangles + i)->Message, NULL, &((triangles +i)->number));
        SDL_FreeSurface((triangles + i)->surfaceMessage);
        SDL_DestroyTexture((triangles + i)->Message);
    }

}




int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    if (TTF_Init() != 0)
    {
        printf("%s", TTF_GetError());
    }
    TTF_Font *sans = TTF_OpenFont("/home/tara/Desktop/project/Sans.ttf", 20);
    if(!sans) 
    {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    triangle triangles [9];
    mouse Mouse; 
    Mouse.src = 0;
    Mouse.dest = 0;
    char test [50];
    dest destination;
    dest origin;
    initialize(triangles);
    centercalculator(triangles, 9);
    rectinitializer(triangles, 9);
    SDL_bool shallExit = SDL_FALSE;
    Uint32 redback = 0x099999ff, blueback = 0x09ffcc99;
    int hi;

    clock_t initialtime = clock ();

    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, 
                                             SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 
                                                   SDL_RENDERER_PRESENTVSYNC | 
                                                   SDL_RENDERER_ACCELERATED);

 

    while (shallExit == SDL_FALSE) 
    {
        SDL_SetRenderDrawColor(sdlRenderer, 0xe0, 0xe0, 0xe0, 0xff);
        SDL_RenderClear(sdlRenderer);
        drawmap(triangles, sdlRenderer);
        drawcastle(triangles, 9, sdlRenderer);
    
        textgenerator(triangles, sdlRenderer, 9);

        
        for (int i = 0; i < 9; i++)
        {
            if ( (triangles + i)->background != 0xff808080)
            {
                if ( (triangles + i)->background != 0xff9999ff && (triangles + i)->background != 0xffffcc99 )
                    (triangles + i)->background += 0x01000000;
                if ((triangles + i)->soldiernum < 50)
                {
                    (triangles + i)->counter ++ ;
                    (triangles + i)->soldiernum = (triangles + i)->counter / 10;
                }                
            }         
        }
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
        SDL_Event sdlEvent;
            while (SDL_PollEvent(&sdlEvent)) 
            {
                switch (sdlEvent.type) 
                {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        Mouse.src = sourcefinder(triangles, 9, &sdlEvent);
                        origin.x = sdlEvent.button.x;
                        origin.y = sdlEvent.button.y;
                        break;
                    }
                    case SDL_MOUSEBUTTONUP :
                    {
                        Mouse.dest = destfinder(triangles, 9, &sdlEvent);
                        destination.x = sdlEvent.button.x;
                        destination.y = sdlEvent.button.y;
                        break;  
                    }
                }
            }
            if (Mouse.src)
            {
                soldier soldiers [Mouse.src];
                Sint16 cos = (destination.x - origin.x) / sqrt( ((destination.x - origin.x) * (destination.x - origin.x)) + 
                                                                ((destination.y - origin.y) * (destination.y - origin.y)) );
                Sint16 sin = (destination.y - origin.y) / sqrt( ((destination.x - origin.x) * (destination.x - origin.x)) + 
                                                                ((destination.y - origin.y) * (destination.y - origin.y)) );
                        
                for (int i = 0; i < (triangles + Mouse.src)->soldiernum; i++)
                {
                    (soldiers + i)->x = origin.x;
                    (soldiers + i)->y = origin.y;
                    (soldiers + i)->color = 0xff000099;
                }
                for (int i = 0; i < (triangles + Mouse.src)->soldiernum; i++)
                {
                    for (int j = 0; j < i; j++)
                    {
                        filledCircleColor(sdlRenderer,(soldiers + j)->x, (soldiers + j)->y, (soldiers + j)->r, (soldiers + j)->color );
                        (soldiers + j)->x += cos * 5;
                        (soldiers + j)->y += sin * 5;
                    }
                    SDL_RenderPresent(sdlRenderer);
                    SDL_Delay(1000 / FPS);
                }
                Mouse.src = 0;
            }
            if (Mouse.src && Mouse.dest)
                {
                    int temp = (triangles + Mouse.src)->soldiernum;
                    (triangles + Mouse.src)->soldiernum = 0;
                    (triangles + Mouse.src)->counter = 0;
                    (triangles + Mouse.dest)->soldiernum += temp;
                    Mouse.src = 0;
                    Mouse.dest = 0;
                }

            
    }


    SDL_DestroyWindow(sdlWindow);

    TTF_Quit();
    SDL_Quit();
}
