#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <hi.h>
#include <Menu.h>
#define true 1;

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 1500;
time_t t1;

typedef struct dest 
{
    Sint16 x;
    Sint16 y;
}dest;

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
   
    srand((unsigned)time(&t1));
    triangle triangles [9];
    potion potion;
    potion.type = 0;

    mouse Mouse; 
    Mouse.src = 0;
    Mouse.dest = 0;
    mouse Menumouse;
    Menumouse.x = 0;
    Menumouse.y = 0;
    dest destination;
    destination.x = 0;
    destination.y = 0;
    dest origin;
    int srctime = 0;
    int desttime = 0;

    int beginattack = 0;
    int initializeattack = 0;
    int attackongoing = 0;
    int attackvalidation = 0;
    double* cos = (double*)malloc(sizeof(double));
    double* sin = (double*)malloc(sizeof(double));
 //   attack attack;

    int opbeginattack = 0;
    opponent opp;
    int opattackinit = 0;
    int opattackongoing = 0;
    double* opcos = (double*)malloc(sizeof(double));
    double* opsin = (double*)malloc(sizeof(double));
    soldier* opsoldiers;


    initialize(triangles);
    centercalculator(triangles, 9);
    rectinitializer(triangles, 9);
    SDL_bool shallExit = SDL_FALSE;
    Uint32 redback = 0x099999ff, blueback = 0x09ffcc99;

    SDL_Window *sdlwindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, 
                                             SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlrenderer = SDL_CreateRenderer(sdlwindow, -1, 
                                                   SDL_RENDERER_PRESENTVSYNC | 
                                                   SDL_RENDERER_ACCELERATED);

    SDL_Rect testr;
    testr.x = 500;
    testr.y = 500;
    testr.h = 200;
    testr.w = 200;
    SDL_bool button = SDL_FALSE;
    SDL_Rect begingame;
    SDL_Rect previousgame;
    SDL_Rect Scoreboard;
    menubuttons(&begingame, &previousgame, &Scoreboard);
    while ( button == SDL_FALSE && shallExit == SDL_FALSE)
    {
        SDL_SetRenderDrawColor(sdlrenderer, 0xe0, 0xe0, 0xe0, 0xff);
        SDL_RenderClear(sdlrenderer);
        SDL_SetRenderDrawColor(sdlrenderer, 0x33, 0x00, 0x66, 0xff);
        SDL_RenderFillRect(sdlrenderer, &begingame);
        SDL_RenderFillRect(sdlrenderer, &previousgame);
        SDL_RenderFillRect(sdlrenderer, &Scoreboard);
        menutext(sdlrenderer, &begingame, &previousgame, &Scoreboard);
        SDL_RenderPresent(sdlrenderer);
        SDL_Delay(1000/FPS * 5);
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Menumouse.x = event.button.x;
                    Menumouse.y = event.button.y;
                    if (validate(&begingame, &previousgame, &Scoreboard, &Menumouse))
                        button = SDL_TRUE;
                    break;
            }
        }
    }
    SDL_DestroyRenderer(sdlrenderer);
    SDL_DestroyWindow(sdlwindow);

    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, 
                                             SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 
                                                   SDL_RENDERER_PRESENTVSYNC | 
                                                   SDL_RENDERER_ACCELERATED);
    int potioncounter = 0; int flag = 0; int destcleaner = 0; 
    int* opsrc = (int*)malloc(sizeof(int));
    int* opdest = (int*)malloc(sizeof(int));
    int s, d;
    if (validate(&begingame, &previousgame, &Scoreboard, &Menumouse) == 1 && shallExit == SDL_FALSE)
        {    
            while (shallExit == SDL_FALSE) 
            {
                if (!destcleaner)
                {
                    Mouse.dest = -1;
                    destination.x = 0;
                    destcleaner = 1;
                    Mouse.src = -1;
                }
                SDL_SetRenderDrawColor(sdlRenderer, 0xe0, 0xe0, 0xe0, 0xff);
                SDL_RenderClear(sdlRenderer);
                drawmap(triangles, sdlRenderer);
                drawcastle(triangles, 9, sdlRenderer);
                textgenerator(triangles, sdlRenderer, 9);
                            
                gameprogress(triangles, 9);
                if (!opbeginattack && oppinit(triangles, opsrc, opdest))
                {
                    s = *opsrc;
                    d = *opdest;
                    opbeginattack = 1;
                    opsoldiers = (soldier*) malloc(sizeof(soldier) * 100);
                    opattackongoing = 1;
                    opattackinit = 0;
                    opp.opattacksoldiernum = (triangles + s)->soldiernum;
                    (triangles + s)->soldiernum = 0;
                    (triangles + s)->counter = 0;
                }
                if (opattackongoing)
                {
                    if (!opattackinit)
                    {
                        *opcos = ((triangles + d)->center.x - (triangles + s)->center.x) / sqrt( ((((triangles + d)->center.x - (triangles + s)->center.x) * ((triangles + d)->center.x - (triangles + s)->center.x)) + 
                        (((triangles + d)->center.y - (triangles + s)->center.y) * ((triangles + d)->center.y - (triangles + s)->center.y))) );
                        *opsin = ((triangles + d)->center.y - (triangles + s)->center.y) / sqrt( ((((triangles + d)->center.x - (triangles + s)->center.x) * ((triangles + d)->center.x - (triangles + s)->center.x)) + 
                        (((triangles + d)->center.y - (triangles + s)->center.y) * ((triangles + d)->center.y - (triangles + s)->center.y))) );
                        for (int i = 0; i < opp.opattacksoldiernum; i++)
                        {
                            (opsoldiers + i)->x = (triangles + s)->center.x;
                            (opsoldiers + i)->y = (triangles + s)->center.y;
                            (opsoldiers + i)->color = 0xff663300;
                            (opsoldiers + i)->r = 10;
                        }
                        for (int i = 0; i < opp.opattacksoldiernum ; i++)
                        {
                            // drawmap(triangles, sdlRenderer);
                            // drawcastle(triangles, 9, sdlRenderer);
                            textgenerator(triangles, sdlRenderer, 9);
                                                
                            for (int j = 0; j < i; j++)
                            {
                                if (((opsoldiers + j)->x <= (triangles + d)->center.x - 10 || (opsoldiers + j)->x >= (triangles + d)->center.x + 10) &&
                                ((opsoldiers + j)->y <= (triangles + d)->center.y - 10 || (opsoldiers + j)->y >= (triangles + d)->center.y + 10))
                                {
                                    filledCircleColor(sdlRenderer,(opsoldiers + j)->x, (opsoldiers + j)->y, (opsoldiers + j)->r, (opsoldiers + j)->color );
                                    (opsoldiers + j)->x += (*opcos) * 20;
                                    (opsoldiers + j)->y += (*opsin) * 20;
                                }
                            }
                        
                            SDL_RenderPresent(sdlRenderer);
                            SDL_Delay(1000 / FPS);
                        }
                        opattackinit = 1;
                    }
                    opattackongoing = 0;
                    if (((opsoldiers + opp.opattacksoldiernum - 1)->x <= (triangles + d)->center.x - 10 || 
                        (opsoldiers + opp.opattacksoldiernum - 1)->x >= (triangles + d )->center.x + 10) &&
                        ((opsoldiers + opp.opattacksoldiernum - 1)->y <= (triangles + d)->center.y - 10 || 
                        (opsoldiers + opp.opattacksoldiernum - 1)->y >= (triangles + d)->center.y + 10))
                        opattackongoing = 1;
                    if (opattackongoing)
                        {
                            for ( int i = 0; i < opp.opattacksoldiernum; i++)
                            {
                                if (((opsoldiers + i)->x <= (triangles + d)->center.x - 10 || (opsoldiers + i)->x >= (triangles + d)->center.x + 10) &&
                                    ((opsoldiers + i)->y <= (triangles + d)->center.y - 10 || (opsoldiers + i)->y >= (triangles + d)->center.y + 10))
                                    {
                                        filledCircleColor(sdlRenderer,(opsoldiers + i)->x, (opsoldiers + i)->y, (opsoldiers + i)->r, (opsoldiers + i)->color );
                                        (opsoldiers + i)->x += (*opcos) * 20;
                                        (opsoldiers + i)->y += (*opsin) * 20;
                                    }
                            }   
                        }
                        else
                        {
                            free(opsoldiers);
                            *opsrc = 0;
                            *opdest = 0;
                            opattackongoing = 0;
                            opbeginattack = 0;
                            int* temp = (int*)malloc(sizeof(int));
                            *temp = opp.opattacksoldiernum;
                                if ((triangles + d)->flag)
                                {
                                    if ((triangles + d)->soldiernum >= *temp)
                                    {
                                        (triangles + d)->soldiernum -= *temp;
                                        (triangles + d)->counter = (triangles + d)->soldiernum * 15;
                                    }
                                    else
                                    {
                                        (triangles + d)->soldiernum = *temp - (triangles + d)->soldiernum;
                                        (triangles + d)->counter = (triangles + d)->soldiernum * 15;
                                        (triangles + d)->flag = 0;
                                        if ((triangles + d)->soldiernum < 10)
                                            (triangles + d)->background = 0x09ffcc99;
                                        else if ((triangles + d)->soldiernum < 30)
                                            (triangles + d)->background = 0xf0ffcc99;
                                        else
                                            (triangles + d)->background = 0xffffcc99;
                                    }
                                }
                                else if ((triangles + d)->background == 0xff808080) 
                                {
                                    if ((triangles + d)->soldiernum >= *temp)
                                    {
                                        (triangles + d)->soldiernum -= *temp;
                                        (triangles + d)->counter = (triangles + d)->soldiernum * 15;
                                    }
                                    else
                                    {
                                        (triangles + d)->soldiernum = *temp - (triangles + d)->soldiernum;
                                        (triangles + d)->counter = (triangles + d)->soldiernum * 15;
                                        if ((triangles + d)->soldiernum < 10)
                                            (triangles + d)->background = 0x09ffcc99;
                                        else if ((triangles + d)->soldiernum < 30)
                                            (triangles + d)->background = 0xf0ffcc99;
                                        else
                                            (triangles + d)->background = 0xffffcc99;
                                    }
                                }
                                else
                                {
                                    (triangles + d)->soldiernum += *temp;
                                    (triangles + d)->counter = (triangles + d)->soldiernum * 15; 
                                }
                            free(temp);
                        }
                }
                if (!flag)
                {
                    createpotion(&potion);
                    potioncoordinator(&potion);
                }
                if (potion.type && potioncounter < 100)
                {
                    flag =  1;
                    potionrenderer(&potion, sdlRenderer);
                    potioncounter++;
                }
                if (flag == 1 && potioncounter == 50)
                {
                    flag = 0;
                    potion.type = 0;
                    potioncounter = 0;
                }

                SDL_RenderPresent(sdlRenderer);
                SDL_Delay(1000 / FPS);
                SDL_Event sdlEvent; 
                
                if (destination.x && origin.x && Mouse.src >= 0 &&
                    (destination.x - origin.x >= 30 || origin.x - destination.x >= 30 || 
                    origin.y - destination.y >= 30 || destination.y - origin.y >= 30) && !beginattack)
                    {
                        attackvalidation = 1;
                        beginattack = 1;
                    }
                if (attackvalidation) 
                {
                    (triangles + Mouse.src)->attacksoldiernum = (triangles + Mouse.src)->soldiernum;
                    (triangles + Mouse.src)->soldiers = (soldier*) malloc(sizeof(soldier) * 100);
                    attackvalidation = 0;
                    attackongoing = 1;
                    initializeattack = 0;
                    (triangles + Mouse.src)->soldiernum = 0;
                    (triangles + Mouse.src)->counter = 0;
                }
                if (attackongoing)
                {  
                    if (initializeattack == 0)
                    {                 
                        *cos = (destination.x - origin.x) / sqrt( ((destination.x - origin.x) * (destination.x - origin.x)) + 
                        ((destination.y - origin.y) * (destination.y - origin.y)) );
                        *sin = (destination.y - origin.y) / sqrt( ((destination.x - origin.x) * (destination.x - origin.x)) + 
                        ((destination.y - origin.y) * (destination.y - origin.y)) );
                    for (int i = 0; i < (triangles + Mouse.src)->attacksoldiernum; i++)
                    {
                        (((triangles + Mouse.src)->soldiers) + i)->x = origin.x;
                        (((triangles + Mouse.src)->soldiers) + i)->y = origin.y;
                        (((triangles + Mouse.src)->soldiers) + i)->color = 0xff000099;
                        (((triangles + Mouse.src)->soldiers) + i)->r = 10;
                    }
                    for (int i = 0; i < (triangles + Mouse.src)->attacksoldiernum; i++)
                    {
                        // drawmap(triangles, sdlRenderer);
                        // drawcastle(triangles, 9, sdlRenderer);
                        textgenerator(triangles, sdlRenderer, 9);
                                        
                        for (int j = 0; j < i; j++)
                        {
                            if (((((triangles + Mouse.src)->soldiers) + j)->x <= destination.x - 10 || (((triangles + Mouse.src)->soldiers) + j)->x >= destination.x + 10) &&
                                ((((triangles + Mouse.src)->soldiers) + j)->y <= destination.y - 10 || (((triangles + Mouse.src)->soldiers) + j)->y >= destination.y + 10))
                            {
                                filledCircleColor(sdlRenderer,(((triangles + Mouse.src)->soldiers) + j)->x, (((triangles + Mouse.src)->soldiers) + j)->y, (((triangles + Mouse.src)->soldiers) + j)->r, (((triangles + Mouse.src)->soldiers) + j)->color );
                                (((triangles + Mouse.src)->soldiers) + j)->x += (*cos) * 20;
                                (((triangles + Mouse.src)->soldiers) + j)->y += (*sin) * 20;
                            }
                        }
                        SDL_RenderPresent(sdlRenderer);
                        SDL_Delay(1000 / FPS);
                    }
                    initializeattack = 1;
                    }
                attackongoing = 0;
                if ( ((((triangles + Mouse.src)->soldiers) + ((triangles + Mouse.src)->attacksoldiernum) - 1)->x <= destination.x - 10 || 
                    (((triangles + Mouse.src)->soldiers) + ((triangles + Mouse.src)->attacksoldiernum) - 1)->x >= destination.x + 10 ) &&
                    ((((triangles + Mouse.src)->soldiers) + ((triangles + Mouse.src)->attacksoldiernum) - 1)->y <= destination.y - 10 || 
                    (((triangles + Mouse.src)->soldiers) + ((triangles + Mouse.src)->attacksoldiernum) - 1)->y >= destination.y + 10))
                    attackongoing = 1;
                if (attackongoing)
                {
                    for ( int i = 0; i < (triangles + Mouse.src)->attacksoldiernum; i++)
                    {
                        if (((((triangles + Mouse.src)->soldiers) + i)->x <= destination.x - 10 || (((triangles + Mouse.src)->soldiers) + i)->x >= destination.x + 10) &&
                        ((((triangles + Mouse.src)->soldiers) + i)->y <= destination.y - 10 || (((triangles + Mouse.src)->soldiers) + i)->y >= destination.y + 10))
                        {
                            filledCircleColor(sdlRenderer,(((triangles + Mouse.src)->soldiers) + i)->x, (((triangles + Mouse.src)->soldiers) + i)->y, (((triangles + Mouse.src)->soldiers) + i)->r, (((triangles + Mouse.src)->soldiers) + i)->color );
                            (((triangles + Mouse.src)->soldiers) + i)->x += (*cos) * 20;
                            (((triangles + Mouse.src)->soldiers) + i)->y += (*sin) * 20;
                        }
                    }
                }
                else 
                {
                    origin.x = 0;
                    destination.x = 0;
                    free(((triangles + Mouse.src)->soldiers));
                    attackvalidation = 0;
                    attackongoing = 0;
                    beginattack = 0;
                }             
                }
                if (Mouse.src >= 0 && Mouse.dest >= 0 && Mouse.src != Mouse.dest && !beginattack)
                {
                    if ((triangles + Mouse.dest)->flag)
                    {
                        int temp = (triangles + Mouse.src)->attacksoldiernum;
                        // (triangles + Mouse.src)->soldiernum = 0;
                        // (triangles + Mouse.src)->counter = 0;
                        (triangles + Mouse.dest)->soldiernum += temp;
                        (triangles + Mouse.dest)->counter += temp * 15;
                        Mouse.src = -1;
                        Mouse.dest = -1;
                    }
                    else 
                    {
                        if ( (triangles + Mouse.dest)->soldiernum >= (triangles + Mouse.src)->attacksoldiernum)
                        {
                            (triangles + Mouse.dest)->soldiernum -= (triangles + Mouse.src)->attacksoldiernum;
                            (triangles + Mouse.dest)->counter -= (triangles + Mouse.src)->attacksoldiernum * 15;
                            // (triangles + Mouse.src)->soldiernum = 0;
                            // (triangles + Mouse.src)->counter = 0;
                            Mouse.src = -1;
                        }
                        else 
                        {
                            (triangles + Mouse.dest)->flag = 1;
                            (triangles + Mouse.dest)->soldiernum = (triangles + Mouse.src)->attacksoldiernum - (triangles + Mouse.dest)->soldiernum;
                            if ( (triangles + Mouse.dest)->soldiernum < 10 )
                                (triangles + Mouse.dest)->background = 0x099999ff;
                            else if ((triangles + Mouse.dest)->soldiernum > 10 && (triangles + Mouse.dest)->soldiernum < 30)
                                (triangles + Mouse.dest)->background = 0x909999ff;
                            else
                                (triangles + Mouse.dest)->background = 0xff9999ff;
                                (triangles + Mouse.dest)->counter = (triangles + Mouse.dest)->soldiernum * 15;
                                // (triangles + Mouse.src)->soldiernum = 0;
                                // (triangles + Mouse.src)->counter = 0;
                                Mouse.src = -1;
                        }
                    }
                Mouse.dest = -1;
                destination.x = 0;
                }
                SDL_RenderPresent(sdlRenderer);
                SDL_Delay(1000 / FPS);
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
                            break;
                        }
                        case SDL_MOUSEBUTTONUP :
                        {
                            Mouse.dest = destfinder(triangles, 9, &sdlEvent, &Mouse);
                            destination.x = sdlEvent.button.x;
                            destination.y = sdlEvent.button.y;
                            break;  
                        }
                    }
                } 
            }
        }
                  //  }
                    // else if (validate(&begingame, &previousgame, &Scoreboard, &Menumouse) == 2)
                    // {

                    // }
                    // else if (validate(&begingame, &previousgame, &Scoreboard, &Menumouse) == 3)
                    // {

    SDL_DestroyRenderer(sdlrenderer);
    SDL_DestroyWindow(sdlwindow);
    TTF_CloseFont(sans);
    TTF_Quit();
    SDL_Quit();
}