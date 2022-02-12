//Main game
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include "headers.h"


int maingame(int map)
{
    const int SCREEN_WIDTH = 1500;
    const int SCREEN_HEIGHT = 1500;
    const int FPS = 55;
    time_t t1;
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
   
    srand((unsigned)time(&t1));
    triangle triangles [11];
    potion potion;
    potion.type = 0;

    // int msrc [100];
    // int mdest [100];

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
    SDL_Rect time;

    int beginattack = 0;
    int initializeattack = 0;
    int attackongoing = 0;
    int u = 0;
    int attackvalidation = 0;
    double* cos = (double*)malloc(sizeof(double));
    double* sin = (double*)malloc(sizeof(double));

    int opbeginattack = 0;
    opponent opp;
    int opattackinit = 0;
    int q = 0;
    int opattackongoing = 0;
    double* opcos = (double*)malloc(sizeof(double));
    double* opsin = (double*)malloc(sizeof(double));
    soldier* opsoldiers;

    // switch (map) 
    // {
    //     case 1 :
    //         initialize1(triangles);
    //         break;
    //     case 2 :
    //         initialize2(triangles);
    //         break;
    //     case 3 :
    //         initialize3(triangles);
    //         break;
    // }
    initializetest(triangles);
    centercalculator(triangles, 11);
    rectinitializer(triangles, 11);
    SDL_bool shallExit = SDL_FALSE;
    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, 
                                             SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 
                                                   SDL_RENDERER_PRESENTVSYNC | 
                                                   SDL_RENDERER_ACCELERATED);
    int potioncounter = 0; int flag = 0; int destcleaner = 0; potion.stopattack = 0; potion.rgameprogress = 15;
    potion.r = 1; potion.attack = 1; potion.activeforopp = 0; potion.rp = 1;
    int* opsrc = (int*)malloc(sizeof(int));
    int* opdest = (int*)malloc(sizeof(int));
    int s, d; int endgame = 0;
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
                drawtestmap(triangles, sdlRenderer);
                drawcastle(triangles, 11, sdlRenderer);
                textgenerator(triangles, sdlRenderer, 11);
                            
                gameprogress(triangles, 11, potion.rgameprogress, potion.activeforopp);
                if (!opbeginattack && oppinit(triangles, 11, opsrc, opdest, &potion))
                {
                    if (!potion.stopattack || potion.activeforopp)
                    {
                        s = *opsrc;
                        d = *opdest;
                        opbeginattack = 1;
                        opsoldiers = (soldier*) malloc(sizeof(soldier) * 300);
                        opattackongoing = 1;
                        opattackinit = 0;
                        opp.opattacksoldiernum = (triangles + s)->soldiernum;
                        (triangles + s)->soldiernum = 0;
                        (triangles + s)->counter = 0;
                        q = 0;
                    }
                }
                if (opattackongoing)
                {
                    if (!opattackinit)
                    {
                        *opcos = ((triangles + d)->center.x - (triangles + s)->center.x) / sqrt( ((((triangles + d)->center.x - (triangles + s)->center.x) * ((triangles + d)->center.x - (triangles + s)->center.x)) + 
                        (((triangles + d)->center.y - (triangles + s)->center.y) * ((triangles + d)->center.y - (triangles + s)->center.y))) );
                        *opsin = ((triangles + d)->center.y - (triangles + s)->center.y) / sqrt( ((((triangles + d)->center.x - (triangles + s)->center.x) * ((triangles + d)->center.x - (triangles + s)->center.x)) + 
                        (((triangles + d)->center.y - (triangles + s)->center.y) * ((triangles + d)->center.y - (triangles + s)->center.y))) );
                        if (q == 0)
                        {
                            for (int j = 0; j < opp.opattacksoldiernum; j++)
                            {
                                (opsoldiers + j)->x = (triangles + s)->center.x;
                                (opsoldiers + j)->y = (triangles + s)->center.y;
                                (opsoldiers + j)->color = 0xff663300;
                                (opsoldiers + j)->r = 10;
                            }
                        }
                        if (q < opp.opattacksoldiernum)
                        {
                            textgenerator(triangles, sdlRenderer, 11);
                            for (int j = 0; j < q; j++)
                            {
                                if (((opsoldiers + j)->x <= (triangles + d)->center.x - 10 || (opsoldiers + j)->x >= (triangles + d)->center.x + 10) &&
                                ((opsoldiers + j)->y <= (triangles + d)->center.y - 10 || (opsoldiers + j)->y >= (triangles + d)->center.y + 10))
                                {
                                    filledCircleColor(sdlRenderer,(opsoldiers + j)->x, (opsoldiers + j)->y, (opsoldiers + j)->r, (opsoldiers + j)->color );
                                    (opsoldiers + j)->x += (*opcos) * 20 * potion.rp;
                                    (opsoldiers + j)->y += (*opsin) * 20 * potion.rp;
                                }
                            }
                            if (hitpotion((opsoldiers + 0), &potion) && !potion.flag)
                            {
                                flag = 1;
                                potion.counter = 0;
                                potion.flag = 1;
                                potion.activeforopp = 1;
                                potioninit(&potion);
                            }
                        q++;
                        }
                        else if (q == opp.opattacksoldiernum) { opattackinit = 1; }
                    }
                    opattackongoing = 0;
                    if (((opsoldiers + opp.opattacksoldiernum - 1)->x <= (triangles + d)->center.x - 10 || 
                        (opsoldiers + opp.opattacksoldiernum - 1)->x >= (triangles + d )->center.x + 10) &&
                        ((opsoldiers + opp.opattacksoldiernum - 1)->y <= (triangles + d)->center.y - 10 || 
                        (opsoldiers + opp.opattacksoldiernum - 1)->y >= (triangles + d)->center.y + 10))
                        opattackongoing = 1;
                    if (opattackongoing && opattackinit) 
                        {
                            for ( int j = 0; j < opp.opattacksoldiernum; j++)
                            {
                                if (((opsoldiers + j)->x <= (triangles + d)->center.x - 10 || (opsoldiers + j)->x >= (triangles + d)->center.x + 10) &&
                                    ((opsoldiers + j)->y <= (triangles + d)->center.y - 10 || (opsoldiers + j)->y >= (triangles + d)->center.y + 10))
                                    {
                                        filledCircleColor(sdlRenderer,(opsoldiers + j)->x, (opsoldiers + j)->y, (opsoldiers + j)->r, (opsoldiers + j)->color );
                                        (opsoldiers + j)->x += (*opcos) * 20 * potion.rp;
                                        (opsoldiers + j)->y += (*opsin) * 20 * potion.rp;
                                    }
                            }
                            if (hitpotion((opsoldiers + 0), &potion) && !potion.flag)
                            {
                                flag = 1;
                                potion.counter = 0;
                                potion.flag = 1;
                                potion.activeforopp = 1;
                                potioninit(&potion);
                            }   
                        }
                        else if (!opattackongoing)
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
                }
                if (potion.type && potioncounter < 150 && !potion.flag)
                {
                    flag =  1;
                    potionrenderer(&potion, sdlRenderer);
                    potioncounter++;
                }
                if (flag && potioncounter == 150 && !potion.flag)
                {
                    flag = 0;
                    potion.type = 0;
                    potioncounter = 0;
                }

            //    SDL_RenderPresent(sdlRenderer);
            //    SDL_Delay(1000 / FPS);
                SDL_Event sdlEvent; 
                
                if (destination.x && origin.x && Mouse.src >= 0 &&
                    (destination.x - origin.x >= 30 || origin.x - destination.x >= 30 || 
                    origin.y - destination.y >= 30 || destination.y - origin.y >= 30) && !beginattack)
                    {
                        if ( potion.type != 1 || !potion.activeforopp )
                        {
                            attackvalidation = 1;
                            beginattack = 1;
                        }
                    }
                if (attackvalidation) 
                {
                    (triangles + Mouse.src)->attacksoldiernum = (triangles + Mouse.src)->soldiernum;
                    (triangles + Mouse.src)->soldiers = (soldier*) malloc(sizeof(soldier) * 300);
                    attackvalidation = 0;
                    attackongoing = 1;
                    initializeattack = 0;
                    (triangles + Mouse.src)->soldiernum = 0;
                    (triangles + Mouse.src)->counter = 0;
                    u = 0;
                }
                if (attackongoing)
                {  
                    if (!initializeattack)
                    {              
                        *cos = (destination.x - origin.x) / sqrt( ((destination.x - origin.x) * (destination.x - origin.x)) + 
                        ((destination.y - origin.y) * (destination.y - origin.y)) );
                        *sin = (destination.y - origin.y) / sqrt( ((destination.x - origin.x) * (destination.x - origin.x)) + 
                        ((destination.y - origin.y) * (destination.y - origin.y)) );
                    if (!u){
                    for (int i = 0; i < (triangles + Mouse.src)->attacksoldiernum; i++)
                    {
                        (((triangles + Mouse.src)->soldiers) + i)->x = origin.x;
                        (((triangles + Mouse.src)->soldiers) + i)->y = origin.y;
                        (((triangles + Mouse.src)->soldiers) + i)->color = 0xff000099;
                        (((triangles + Mouse.src)->soldiers) + i)->r = 10;
                    }}
                    if (u < (triangles + Mouse.src)->attacksoldiernum)
                    {
                        textgenerator(triangles, sdlRenderer, 11);
                                        
                        for (int j = 0; j < u; j++)
                        {
                            if (((((triangles + Mouse.src)->soldiers) + j)->x <= destination.x - 10 || (((triangles + Mouse.src)->soldiers) + j)->x >= destination.x + 10) &&
                                ((((triangles + Mouse.src)->soldiers) + j)->y <= destination.y - 10 || (((triangles + Mouse.src)->soldiers) + j)->y >= destination.y + 10))
                            {
                                filledCircleColor(sdlRenderer,(((triangles + Mouse.src)->soldiers) + j)->x, (((triangles + Mouse.src)->soldiers) + j)->y, (((triangles + Mouse.src)->soldiers) + j)->r, (((triangles + Mouse.src)->soldiers) + j)->color );
                                (((triangles + Mouse.src)->soldiers) + j)->x += (*cos) * 20 * potion.r;
                                (((triangles + Mouse.src)->soldiers) + j)->y += (*sin) * 20 * potion.r;
                            }
                        }
                        if (hitpotion(((triangles + Mouse.src)->soldiers + 0), &potion) && !potion.flag)
                                {
                                    flag = 1;
                                    potion.counter = 0;
                                    potion.flag = 1;
                                    potioninit(&potion);
                                } 
                        u++;
                    }
                    else if (u == (triangles + Mouse.src)->attacksoldiernum)
                        {initializeattack = 1;}
                    }
                attackongoing = 0;
                if ( ((((triangles + Mouse.src)->soldiers) + ((triangles + Mouse.src)->attacksoldiernum) - 1)->x <= destination.x - 10 || 
                    (((triangles + Mouse.src)->soldiers) + ((triangles + Mouse.src)->attacksoldiernum) - 1)->x >= destination.x + 10 ) &&
                    ((((triangles + Mouse.src)->soldiers) + ((triangles + Mouse.src)->attacksoldiernum) - 1)->y <= destination.y - 10 || 
                    (((triangles + Mouse.src)->soldiers) + ((triangles + Mouse.src)->attacksoldiernum) - 1)->y >= destination.y + 10))
                    attackongoing = 1;
                if (attackongoing && initializeattack)
                {
                    for ( int i = 0; i < (triangles + Mouse.src)->attacksoldiernum; i++)
                    {
                        if (((((triangles + Mouse.src)->soldiers) + i)->x <= destination.x - 10 || (((triangles + Mouse.src)->soldiers) + i)->x >= destination.x + 10) &&
                        ((((triangles + Mouse.src)->soldiers) + i)->y <= destination.y - 10 || (((triangles + Mouse.src)->soldiers) + i)->y >= destination.y + 10))
                        {
                            filledCircleColor(sdlRenderer,(((triangles + Mouse.src)->soldiers) + i)->x, (((triangles + Mouse.src)->soldiers) + i)->y, (((triangles + Mouse.src)->soldiers) + i)->r, (((triangles + Mouse.src)->soldiers) + i)->color );
                            (((triangles + Mouse.src)->soldiers) + i)->x += (*cos) * 20 * potion.r;
                            (((triangles + Mouse.src)->soldiers) + i)->y += (*sin) * 20 * potion.r;
                            
                        }
                    }
                    if (hitpotion(((triangles + Mouse.src)->soldiers + 0), &potion) && !potion.flag)
                    {
                        flag = 1;
                        potion.counter = 0;
                        potion.flag = 1;
                        potioninit(&potion);
                    }
                }
                else if (!attackongoing)
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
                                Mouse.src = -1;
                        }
                    }
                Mouse.dest = -1;
                destination.x = 0;
                }
                if (potion.flag && (potion.counter < potion.countmax))
                {
                    potion.counter ++;
                    potiontime(sdlRenderer, &potion);
                    potiontext(&potion, sdlRenderer);
                }
                if (potion.counter == potion.countmax)
                {
                    flag = 0;
                    potion.flag = 0;
                    potioncounter = 0;
                    potionquit(&potion);
                    potion.activeforopp = 0;
                }
                int j = 0; int k = 0;
                for (int i = 0; i < 11; i++)
                {
                    if ((triangles + i)->flag)
                        j++;
                }
                if (j == 11)
                {
                    endgame = 1;
                    return endgame;
                }
                if (j == 0)
                {
                    endgame = 2;
                    return endgame;
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
                            return 0;
                        case SDL_MOUSEBUTTONDOWN:
                        {
                            Mouse.src = sourcefinder(triangles, 9, &sdlEvent, &Mouse);
                            if (potion.activeforopp && potion.type == 1) {Mouse.src = -1;}
                            origin.x = (triangles + Mouse.src)->center.x;
                            origin.y = (triangles + Mouse.src)->center.y;
                            break;
                        }
                        case SDL_MOUSEBUTTONUP :
                        {
                            Mouse.dest = destfinder(triangles, 11, &sdlEvent, &Mouse);
                            if (potion.activeforopp && potion.type == 4)
                            {
                                if ( !(triangles + Mouse.dest)->flag && ((triangles + Mouse.dest)->background != 0xffe0e0e0))
                                {
                                    Mouse.dest = -1;
                                }
                            }
                            destination.x = sdlEvent.button.x;
                            destination.y = sdlEvent.button.y;
                            break;  
                        }
                    }
                } 
            }
            SDL_DestroyRenderer(sdlRenderer);
            SDL_DestroyWindow(sdlWindow);
            SDL_Quit();
}