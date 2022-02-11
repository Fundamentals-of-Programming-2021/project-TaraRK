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

void gameprogress (triangle* triangles, int n, int a, int flag)
{
    for (int i = 0; i < n; i++)
        {
            if ( (triangles + i)->background != 0xff808080)
            {
                if ( (triangles + i)->background != 0xff9999ff && (triangles + i)->background != 0xffffcc99 )
                    (triangles + i)->background += 0x01000000;
                if ((triangles + i)->soldiernum < 50)
                {
                    if (flag)
                    {
                        if ((triangles + i)->flag)
                        {
                            (triangles + i)->counter ++;
                            (triangles + i)->soldiernum = (triangles + i)->counter / 15;
                        }
                        else
                        {
                            (triangles +i)->counter ++;
                            (triangles + i)->soldiernum = (triangles + i)->counter / a;
                        }
                    }
                    else
                    {
                        if ((triangles + i)->flag)
                        {
                            (triangles + i)->counter ++;
                            (triangles + i)->soldiernum = (triangles + i)->counter / a;

                        }
                        else 
                        {
                            (triangles + i)->counter ++;
                            (triangles + i)->soldiernum = (triangles + i)->counter / 15;
                        }
                    }
                }                
            }         
        }
}
int oppinit(triangle* triangles,int n, int* opsrc, int* opdest, potion* potion)
{
    int a = rand();
    if (a % 50 == 0 )
    {
        *opsrc = rand() % n;
        while ( (triangles + *opsrc)->flag || (triangles + *opsrc)->background == 0xff808080 )
        {
            *opsrc = rand() % n;
        }
        *opdest = rand() % n;
        if ( !(potion->attack))
        {
            while ((triangles + *opdest)->flag)
            {
                *opdest = rand() % n;
            }
        }
        if ((triangles + *opsrc)->soldiernum != 0)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}
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
// void result (SDL_Renderer* renderer, int n)
// {
//     if (n == 1)
//     {
//         SDL_SetRenderDrawColor(renderer, 0x99, 0xff, 0xcc, 0xff);
//         SDL_RenderClear(renderer);
//         textmaker(renderer, 400, 400, "YOU WON");
//         SDL_RenderPresent(renderer);
//     }
//     else if (n == 2)
//     {
//         SDL_SetRenderDrawColor(renderer, 0xff, 0xcc, 0xcc, 0xff);
//         SDL_RenderClear(renderer);
//         textmaker(renderer, 400, 400, "YOU LOST");
//         SDL_RenderPresent(renderer);
//     }
// }
