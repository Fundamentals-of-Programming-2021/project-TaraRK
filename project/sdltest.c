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
time_t t1;
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
int sourcefinder (triangle* triangles, int n, SDL_Event* event, mouse* Mouse)
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
    return -1;
}

int destfinder (triangle* triangles, int n, SDL_Event* event, mouse* Mouse)
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
    return -1;
}



void textgenerator(triangle* triangles, SDL_Renderer* renderer, int n)
{
    if (TTF_Init() != 0)
    {
        printf("%s", TTF_GetError());
    }
    TTF_Font *sans = TTF_OpenFont("/home/tara/Desktop/project/Sans.ttf", 20);
    if(!sans) 
    {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    for (int i = 0; i < n; i++)
    {
        inttostr((triangles + i)->soldiernum, (triangles + i)->numstr);
        SDL_Surface* surface;
        SDL_Texture* texture;
        // (triangles + i)->surfaceMessage = TTF_RenderText_Solid(sans, (triangles + i)->numstr, black);
        // (triangles + i)->Message = SDL_CreateTextureFromSurface(renderer, (triangles + i)->surfaceMessage);
        surface = TTF_RenderText_Solid(sans, (triangles + i)->numstr, black);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &((triangles +i)->number));
        // SDL_FreeSurface((triangles + i)->surfaceMessage);
        // SDL_DestroyTexture((triangles + i)->Message);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
    TTF_CloseFont(sans);
    TTF_Quit(); 
}




int main(void)
{ 
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    
   
    srand((unsigned)time(&t1));
    triangle triangles [9];
    mouse Mouse; 
    Mouse.src = 0;
    Mouse.dest = 0;
    dest destination;
    destination.x = 0;
    destination.y = 0;
    dest origin;
    int srctime = 0;
    int desttime = 0;

    initialize(triangles);
    centercalculator(triangles, 9);
    rectinitializer(triangles, 9);
    SDL_bool shallExit = SDL_FALSE;
    Uint32 redback = 0x099999ff, blueback = 0x09ffcc99;

    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, 
                                             SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 
                                                   SDL_RENDERER_PRESENTVSYNC | 
                                                   SDL_RENDERER_ACCELERATED);

    // SDL_Rect testr;
    // testr.x = 500;
    // testr.y = 500;
    // testr.h = 200;
    // testr.w = 200;
    // SDL_bool entergame = 
    // while 



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
                    (triangles + i)->soldiernum = (triangles + i)->counter / 15;
                }                
            }         
        }
        int a = rand();
        if (a % 35 == 0 )
        {
            int* opsrc = (int*)malloc(sizeof(int));
            *opsrc = 0;
            while ( (triangles + *opsrc)->flag || (triangles + *opsrc)->background == 0xff808080 )
            {
                *opsrc = rand() % 9;
            }
            int* opdest = (int*)malloc(sizeof(int));
            *opdest = rand() % 9;
            soldier* opsoldiers = (soldier*)malloc(sizeof(soldier) * (triangles + *opsrc)->soldiernum);
            double* cos = (double*)malloc(sizeof(double));
            *cos = ((triangles + *opdest)->center.x - (triangles + *opsrc)->center.x) / sqrt( ((((triangles + *opdest)->center.x - (triangles + *opsrc)->center.x) * ((triangles + *opdest)->center.x - (triangles + *opsrc)->center.x)) + 
                                                    (((triangles + *opdest)->center.y - (triangles + *opsrc)->center.y) * ((triangles + *opdest)->center.y - (triangles + *opsrc)->center.y))) );
            double* sin = (double*)malloc(sizeof(double));
            *sin = ((triangles + *opdest)->center.y - (triangles + *opsrc)->center.y) / sqrt( ((((triangles + *opdest)->center.x - (triangles + *opsrc)->center.x) * ((triangles + *opdest)->center.x - (triangles + *opsrc)->center.x)) + 
                                                    (((triangles + *opdest)->center.y - (triangles + *opsrc)->center.y) * ((triangles + *opdest)->center.y - (triangles + *opsrc)->center.y))) );
            for (int i = 0; i < (triangles + *opsrc)->soldiernum; i++)
                {
                    (opsoldiers + i)->x = (triangles + *opsrc)->center.x;
                    (opsoldiers + i)->y = (triangles + *opsrc)->center.y;
                    (opsoldiers + i)->color = 0xff663300;
                    (opsoldiers + i)->r = 10;
                }
            for (int i = 0; i < (triangles + *opsrc)->soldiernum; i++)
                {
                    drawmap(triangles, sdlRenderer);
                    drawcastle(triangles, 9, sdlRenderer);
                    textgenerator(triangles, sdlRenderer, 9);
                    
                    for (int j = 0; j < i; j++)
                    {
                        if (((opsoldiers + j)->x <= (triangles + *opdest)->center.x - 10 || (opsoldiers + j)->x >= (triangles + *opdest)->center.x + 10) &&
                            ((opsoldiers + j)->y <= (triangles + *opdest)->center.y - 10 || (opsoldiers + j)->y >= (triangles + *opdest)->center.y + 10))
                        {
                            filledCircleColor(sdlRenderer,(opsoldiers + j)->x, (opsoldiers + j)->y, (opsoldiers + j)->r, (opsoldiers + j)->color );
                            (opsoldiers + j)->x += (*cos) * 20;
                            (opsoldiers + j)->y += (*sin) * 20;
                        }
                    }
                    SDL_RenderPresent(sdlRenderer);
                    SDL_Delay(1000 / FPS);
                }
            while( ((opsoldiers + (triangles + *opsrc)->soldiernum - 1)->x <= (triangles + *opdest)->center.x - 10 || 
                    (opsoldiers + (triangles + *opsrc)->soldiernum - 1)->x >= (triangles + *opdest)->center.x + 10) &&
                    ((opsoldiers + (triangles + *opsrc)->soldiernum - 1)->y <= (triangles + *opdest)->center.y - 10 || 
                    (opsoldiers + (triangles + *opsrc)->soldiernum - 1)->y >= (triangles + *opdest)->center.y + 10))
                {
                    drawmap(triangles, sdlRenderer);
                    drawcastle(triangles, 9, sdlRenderer);
                    textgenerator(triangles, sdlRenderer, 9);
                    for ( int i = 0; i < (triangles + *opsrc)->soldiernum; i++)
                    {
                        if (((opsoldiers + i)->x <= (triangles + *opdest)->center.x - 10 || (opsoldiers + i)->x >= (triangles + *opdest)->center.x + 10) &&
                            ((opsoldiers + i)->y <= (triangles + *opdest)->center.y - 10 || (opsoldiers + i)->y >= (triangles + *opdest)->center.y + 10))
                        {
                            filledCircleColor(sdlRenderer,(opsoldiers + i)->x, (opsoldiers + i)->y, (opsoldiers + i)->r, (opsoldiers + i)->color );
                            (opsoldiers + i)->x += (*cos) * 20;
                            (opsoldiers + i)->y += (*sin) * 20;
                        }
                    }
                    SDL_RenderPresent(sdlRenderer);
                    SDL_Delay(1000 / FPS);
                }
            free(opsoldiers);
            free(cos);
            free(sin);
            int* temp = (int*)malloc(sizeof(int));
            *temp = (triangles + *opsrc)->soldiernum;
            (triangles + *opsrc)->soldiernum = 0;
            (triangles + *opsrc)->counter = 0;
            if ((triangles + *opdest)->flag)
            {
                if ((triangles + *opdest)->soldiernum >= *temp)
                {
                    (triangles + *opdest)->soldiernum -= *temp;
                    (triangles + *opdest)->counter = (triangles + *opdest)->soldiernum * 15;
                }
                else
                {
                    (triangles + *opdest)->soldiernum = *temp - (triangles + *opdest)->soldiernum;
                    (triangles + *opdest)->counter = (triangles + *opdest)->soldiernum * 15;
                    (triangles + *opdest)->flag = 0;
                    if ((triangles + *opdest)->soldiernum < 10)
                        (triangles + *opdest)->background = 0x09ffcc99;
                    else if ((triangles + *opdest)->soldiernum < 30)
                        (triangles + *opdest)->background = 0xf0ffcc99;
                    else
                        (triangles + *opdest)->background = 0xffffcc99;
                }
            }
            else if ((triangles + *opdest)->background == 0xff808080) 
            {
                if ((triangles + *opdest)->soldiernum >= *temp)
                {
                    (triangles + *opdest)->soldiernum -= *temp;
                    (triangles + *opdest)->counter = (triangles + *opdest)->soldiernum * 15;
                }
                else
                {
                    (triangles + *opdest)->soldiernum = *temp - (triangles + *opdest)->soldiernum;
                    (triangles + *opdest)->counter = (triangles + *opdest)->soldiernum * 15;
                    if ((triangles + *opdest)->soldiernum < 10)
                        (triangles + *opdest)->background = 0x09ffcc99;
                    else if ((triangles + *opdest)->soldiernum < 30)
                        (triangles + *opdest)->background = 0xf0ffcc99;
                    else
                        (triangles + *opdest)->background = 0xffffcc99;
                }
            }
            else
            {
                (triangles + *opdest)->soldiernum += *temp;
                (triangles + *opdest)->counter = (triangles + *opdest)->soldiernum * 15; 
            }
            drawmap(triangles, sdlRenderer);
            drawcastle(triangles, 9, sdlRenderer);
            textgenerator(triangles, sdlRenderer, 9);
            SDL_RenderPresent(sdlRenderer);
            SDL_Delay(1000 / FPS);
            free(temp);
            free(opdest);
            free(opsrc);
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
                        Mouse.src = sourcefinder(triangles, 9, &sdlEvent, &Mouse);
                        origin.x = (triangles + Mouse.src)->center.x;
                        origin.y = (triangles + Mouse.src)->center.y;
                        srctime = timestamp(&sdlEvent);
                        break;
                    }
                    case SDL_MOUSEBUTTONUP :
                    {
                        Mouse.dest = destfinder(triangles, 9, &sdlEvent, &Mouse);
                        destination.x = sdlEvent.button.x;
                        destination.y = sdlEvent.button.y;
                        desttime = timestamp(&sdlEvent);
                        break;  
                    }
                }
            }
            for (int k = 0; destination.x && origin.x && Mouse.src >= 0 &&
                            (destination.x - origin.x >= 30 || 
                             origin.x - destination.x >= 30 || 
                             origin.y - destination.y >= 30 ||
                             destination.y - origin.y >= 30); k++)
            {
                soldier* soldiers = (soldier*)malloc(sizeof(soldier) * (triangles + Mouse.src)->soldiernum);
            //    soldier soldiers [(triangles + Mouse.src)->soldiernum]; commented for memory management
                double* cos = (double*)malloc(sizeof(double));
                *cos = (destination.x - origin.x) / sqrt( ((destination.x - origin.x) * (destination.x - origin.x)) + 
                                                                ((destination.y - origin.y) * (destination.y - origin.y)) );
                double* sin = (double*)malloc(sizeof(double));
                *sin = (destination.y - origin.y) / sqrt( ((destination.x - origin.x) * (destination.x - origin.x)) + 
                                                                ((destination.y - origin.y) * (destination.y - origin.y)) );
                        
                for (int i = 0; i < (triangles + Mouse.src)->soldiernum; i++)
                {
                    (soldiers + i)->x = origin.x;
                    (soldiers + i)->y = origin.y;
                    (soldiers + i)->color = 0xff000099;
                    (soldiers + i)->r = 10;
                }
                for (int i = 0; i < (triangles + Mouse.src)->soldiernum; i++)
                {
                    drawmap(triangles, sdlRenderer);
                    drawcastle(triangles, 9, sdlRenderer);
                    textgenerator(triangles, sdlRenderer, 9);
                    
                    for (int j = 0; j < i; j++)
                    {
                        if (((soldiers + j)->x <= destination.x - 10 || (soldiers + j)->x >= destination.x + 10) &&
                            ((soldiers + j)->y <= destination.y - 10 || (soldiers + j)->y >= destination.y + 10))
                        {
                            filledCircleColor(sdlRenderer,(soldiers + j)->x, (soldiers + j)->y, (soldiers + j)->r, (soldiers + j)->color );
                            (soldiers + j)->x += (*cos) * 20;
                            (soldiers + j)->y += (*sin) * 20;
                        }
                    }
                    SDL_RenderPresent(sdlRenderer);
                    SDL_Delay(1000 / FPS);

                }
                while( ((soldiers + (triangles + Mouse.src)->soldiernum - 1)->x <= destination.x - 10 || 
                       (soldiers + (triangles + Mouse.src)->soldiernum - 1)->x >= destination.x + 10) &&
                       ((soldiers + (triangles + Mouse.src)->soldiernum - 1)->y <= destination.y - 10 || 
                       (soldiers + (triangles + Mouse.src)->soldiernum - 1)->y >= destination.y + 10))
                {
                    drawmap(triangles, sdlRenderer);
                    drawcastle(triangles, 9, sdlRenderer);
                    textgenerator(triangles, sdlRenderer, 9);
                    for ( int i = 0; i < (triangles + Mouse.src)->soldiernum; i++)
                    {
                        if (((soldiers + i)->x <= destination.x - 10 || (soldiers + i)->x >= destination.x + 10) &&
                            ((soldiers + i)->y <= destination.y - 10 || (soldiers + i)->y >= destination.y + 10))
                        {
                            filledCircleColor(sdlRenderer,(soldiers + i)->x, (soldiers + i)->y, (soldiers + i)->r, (soldiers + i)->color );
                            (soldiers + i)->x += (*cos) * 20;
                            (soldiers + i)->y += (*sin) * 20;
                        }
                    }
                    SDL_RenderPresent(sdlRenderer);
                    SDL_Delay(1000 / FPS);
                }
                origin.x = 0;
                destination.x = 0;
                free(soldiers);
                free(cos);
                free(sin);
            }
            if (Mouse.src >= 0 && Mouse.dest >= 0 && Mouse.src != Mouse.dest)
                {
                    if ((triangles + Mouse.dest)->flag)
                    {
                        int temp = (triangles + Mouse.src)->soldiernum;
                        (triangles + Mouse.src)->soldiernum = 0;
                        (triangles + Mouse.src)->counter = 0;
                        (triangles + Mouse.dest)->soldiernum += temp;
                        (triangles + Mouse.dest)->counter += temp * 15;
                        Mouse.src = -1;
                        Mouse.dest = -1;
                    }
                    else 
                    {
                        if ( (triangles + Mouse.dest)->soldiernum >= 
                             (triangles + Mouse.src)->soldiernum)
                             {
                                (triangles + Mouse.dest)->soldiernum -= (triangles + Mouse.src)->soldiernum;
                                (triangles + Mouse.dest)->counter -= (triangles + Mouse.src)->soldiernum * 15;
                                (triangles + Mouse.src)->soldiernum = 0;
                                (triangles + Mouse.src)->counter = 0;
                                Mouse.src = -1;
                             }
                        else 
                             {
                                (triangles + Mouse.dest)->flag = 1;
                                (triangles + Mouse.dest)->soldiernum = (triangles + Mouse.src)->soldiernum - (triangles + Mouse.dest)->soldiernum;
                                if ( (triangles + Mouse.dest)->soldiernum < 10 )
                                    (triangles + Mouse.dest)->background = 0x099999ff;
                                else if ((triangles + Mouse.dest)->soldiernum > 10 && (triangles + Mouse.dest)->soldiernum < 30)
                                    (triangles + Mouse.dest)->background = 0x909999ff;
                                else
                                    (triangles + Mouse.dest)->background = 0xff9999ff;
                                (triangles + Mouse.dest)->counter = (triangles + Mouse.dest)->soldiernum * 15;
                                (triangles + Mouse.src)->soldiernum = 0;
                                (triangles + Mouse.src)->counter = 0;
                                Mouse.src = -1;
                             }
                    }
                }
            Mouse.dest = -1;
            destination.x = 0;
    }
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}