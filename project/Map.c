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
// #define true 1;
Uint32 background = 0xffe0e0e0;
SDL_Color black2 = {0, 0, 0, 255};
time_t t2;
void randoms ()
{
    srand((unsigned)time(&t2));
}

void inttostr(int a, char* b)
{
    int acopy = a;
    int counter = 0;
    if (a == 0)
    {
        b[0] = '0';
        counter = 1;
    }
    else 
    {
        while (acopy)
        {
            counter ++;
            acopy /= 10;
        }
        acopy = a;
        for (int i = counter - 1; i >= 0; i--)
        { 
            b[i] = (acopy % 10) + '0';
            acopy /= 10;
        }
    }
    b[counter] = '\0';
}

int choosemap(SDL_Renderer * sdlrenderer)
{
    SDL_bool shallExit = SDL_FALSE;
    mouse mouse;
    while (shallExit == SDL_FALSE)
    {
        SDL_SetRenderDrawColor(sdlrenderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(sdlrenderer);
        uploadimage(sdlrenderer, "Map1.jpg", 240, 240);
        uploadimage(sdlrenderer, "Map2.jpg", 760, 240);
        uploadimage(sdlrenderer, "Map3.jpg", 240, 760);
        uploadimage(sdlrenderer, "q.jpg", 760, 760);
        SDL_RenderPresent(sdlrenderer);
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
                if (whichmap(&mouse))
                {
                    return (whichmap(&mouse));
                }
                break;
               
            }
        }
    }
}
int whichmap(mouse* mouse)
{
    if (mouse->x >= 240 && mouse->x <= 740 && mouse->y >= 240 && mouse->y <= 740)
        return 1;
    else if (mouse->x >= 760 && mouse->x <= 1260 && mouse->y >= 240 && mouse->y <= 740)
        return 2;
    else if (mouse->x >= 240 && mouse->x <= 740 && mouse->y >= 760 && mouse->y <= 1260)
        return 3;
    else if (mouse->x >= 760 && mouse->x <= 1260 && mouse->y >= 760 && mouse->y <= 1260)
        return 0;
    else 
        return 0;
}
void uploadimage(SDL_Renderer* renderer, char* name, int x, int y)
{
    SDL_Surface* surface = IMG_Load(name);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = 500;
    rect.w = 500;
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_DestroyTexture(text);
    SDL_FreeSurface(surface);

}
void textgenerator(triangle* triangles, SDL_Renderer* renderer, int n)
{
    TTF_Font *sans = TTF_OpenFont("/home/tara/Desktop/project/Sans.ttf", 20);
    for (int i = 0; i < n; i++)
    {
        inttostr((triangles + i)->soldiernum, (triangles + i)->numstr);
        (triangles + i)->surfaceMessage = TTF_RenderText_Solid(sans, (triangles + i)->numstr, black2);
        (triangles + i)->Message = SDL_CreateTextureFromSurface(renderer, (triangles + i)->surfaceMessage);
        SDL_RenderCopy(renderer, (triangles + i)->Message, NULL, &((triangles +i)->number));
        SDL_FreeSurface((triangles + i)->surfaceMessage);
        SDL_DestroyTexture((triangles + i)->Message);
    }
    TTF_CloseFont(sans);
}


int timestamp (SDL_Event* event)
{
    switch (event->type)
    {
        case (SDL_MOUSEBUTTONDOWN || SDL_MOUSEBUTTONUP ):
            return (event->button.timestamp);
    }
}
void initialize1(triangle* triangles)
{
    for (int i = 0; i < 9; i ++)
    {
        (triangles + i)->flag = 0;
        (triangles + i)->attacksoldiernum = 0;
        (triangles + i)->soldiers = NULL;
        if (i % 3 == 1)
        {
            (triangles + i)->background = 0x099999ff;
            (triangles + i)->soldiernum = 0;
            (triangles + i)->counter = 0;
            (triangles + i)->flag = 1;
        }
        else if (i % 3 == 2)
        {
            (triangles + i)->background = 0x09ffcc99;
            (triangles + i)->soldiernum = 0;
            (triangles + i)->counter = 0;
        }
        else 
        {
            (triangles + i)->background = 0xff808080;
            (triangles + i)->soldiernum = 10;
        }
        
        
    }
    (triangles + 0)->p1.x = 30; (triangles + 0)->p1.y = 30;
    (triangles + 0)->p2.x = 100; (triangles + 0)->p2.y = 30;
    (triangles + 0)->p3.x = 30; (triangles + 0)->p3.y = 100;
    (triangles + 1)->p1.x = 100; (triangles + 1)->p1.y = 30;
    (triangles + 1)->p2.x = 30; (triangles + 1)->p2.y = 100;
    (triangles + 1)->p3.x = 250; (triangles + 1)->p3.y = 250;
    (triangles + 2)->p1.x = 250; (triangles + 2)->p1.y = 250;
    (triangles + 2)->p2.x = 100; (triangles + 2)->p2.y = 30;
    (triangles + 2)->p3.x = 500; (triangles + 2)->p3.y = 200;
    (triangles + 3)->p1.x = 250; (triangles + 3)->p1.y = 250;
    (triangles + 3)->p2.x = 500; (triangles + 3)->p2.y = 200;
    (triangles + 3)->p3.x = 400; (triangles + 3)->p3.y = 600;
    (triangles + 4)->p1.x = 600; (triangles + 4)->p1.y = 370;
    (triangles + 4)->p2.x = 500; (triangles + 4)->p2.y = 200;
    (triangles + 4)->p3.x = 400; (triangles + 4)->p3.y = 600;
    (triangles + 5)->p1.x = 600; (triangles + 5)->p1.y = 370;
    (triangles + 5)->p2.x = 500; (triangles + 5)->p2.y = 700;
    (triangles + 5)->p3.x = 400; (triangles + 5)->p3.y = 600;
    (triangles + 6)->p1.x = 150; (triangles + 6)->p1.y = 500;
    (triangles + 6)->p2.x = 250; (triangles + 6)->p2.y = 250;
    (triangles + 6)->p3.x = 400; (triangles + 6)->p3.y = 600;
    (triangles + 7)->p1.x = 150; (triangles + 7)->p1.y = 500;
    (triangles + 7)->p2.x = 250; (triangles + 7)->p2.y = 250;
    (triangles + 7)->p3.x = 30; (triangles + 7)->p3.y = 100;
    (triangles + 8)->p1.x = 700; (triangles + 8)->p1.y = 200;
    (triangles + 8)->p2.x = 500; (triangles + 8)->p2.y = 200;
    (triangles + 8)->p3.x = 600; (triangles + 8)->p3.y = 370;

}

void initialize2(triangle* triangles)
{
    for (int i = 0; i < 9; i ++)
    {
        (triangles + i)->flag = 0;
        (triangles + i)->attacksoldiernum = 0;
        (triangles + i)->soldiers = NULL;
        if (i % 3 == 1)
        {
            (triangles + i)->background = 0x099999ff;
            (triangles + i)->soldiernum = 0;
            (triangles + i)->counter = 0;
            (triangles + i)->flag = 1;
        }
        else if (i % 3 == 2)
        {
            (triangles + i)->background = 0x09ffcc99;
            (triangles + i)->soldiernum = 0;
            (triangles + i)->counter = 0;
        }
        else 
        {
            (triangles + i)->background = 0xff808080;
            (triangles + i)->soldiernum = 10;
        }
        
        
    }
    (triangles + 0)->p1.x = 200; (triangles + 0)->p1.y = 70;
    (triangles + 0)->p2.x = 70; (triangles + 0)->p2.y = 200;
    (triangles + 0)->p3.x = 350; (triangles + 0)->p3.y = 350;
    (triangles + 1)->p1.x = 200; (triangles + 1)->p1.y = 70;
    (triangles + 1)->p2.x = 350; (triangles + 1)->p2.y = 350;
    (triangles + 1)->p3.x = 500; (triangles + 1)->p3.y = 150;
    (triangles + 2)->p1.x = 250; (triangles + 2)->p1.y = 500;
    (triangles + 2)->p2.x = 70; (triangles + 2)->p2.y = 200;
    (triangles + 2)->p3.x = 350; (triangles + 2)->p3.y = 350;
    (triangles + 3)->p1.x = 250; (triangles + 3)->p1.y = 500;
    (triangles + 3)->p2.x = 350; (triangles + 3)->p2.y = 350;
    (triangles + 3)->p3.x = 360; (triangles + 3)->p3.y = 400;
    (triangles + 4)->p1.x = 350; (triangles + 4)->p1.y = 350;
    (triangles + 4)->p2.x = 360; (triangles + 4)->p2.y = 400;
    (triangles + 4)->p3.x = 600; (triangles + 4)->p3.y = 380;
    (triangles + 5)->p1.x = 250; (triangles + 5)->p1.y = 500;
    (triangles + 5)->p2.x = 280; (triangles + 5)->p2.y = 650;
    (triangles + 5)->p3.x = 360; (triangles + 5)->p3.y = 400;
    (triangles + 6)->p1.x = 350; (triangles + 6)->p1.y = 350;
    (triangles + 6)->p2.x = 500; (triangles + 6)->p2.y = 150;
    (triangles + 6)->p3.x = 600; (triangles + 6)->p3.y = 380;
    (triangles + 7)->p1.x = 360; (triangles + 7)->p1.y = 400;
    (triangles + 7)->p2.x = 600; (triangles + 7)->p2.y = 380;
    (triangles + 7)->p3.x = 610; (triangles + 7)->p3.y = 610;
    (triangles + 8)->p1.x = 360; (triangles + 8)->p1.y = 400;
    (triangles + 8)->p2.x = 280; (triangles + 8)->p2.y = 650;
    (triangles + 8)->p3.x = 610; (triangles + 8)->p3.y = 610;

}
void initialize3(triangle* triangles)
{
    for (int i = 0; i < 9; i ++)
    {
        (triangles + i)->flag = 0;
        (triangles + i)->attacksoldiernum = 0;
        (triangles + i)->soldiers = NULL;
        if (i % 3 == 1)
        {
            (triangles + i)->background = 0x099999ff;
            (triangles + i)->soldiernum = 0;
            (triangles + i)->counter = 0;
            (triangles + i)->flag = 1;
        }
        else if (i % 3 == 2)
        {
            (triangles + i)->background = 0x09ffcc99;
            (triangles + i)->soldiernum = 0;
            (triangles + i)->counter = 0;
        }
        else 
        {
            (triangles + i)->background = 0xff808080;
            (triangles + i)->soldiernum = 10;
        }
        
        
    }
    (triangles + 0)->p1.x = 60; (triangles + 0)->p1.y = 200;
    (triangles + 0)->p2.x = 80; (triangles + 0)->p2.y = 510;
    (triangles + 0)->p3.x = 170; (triangles + 0)->p3.y = 80;
    (triangles + 1)->p1.x = 80; (triangles + 1)->p1.y = 510;
    (triangles + 1)->p2.x = 170; (triangles + 1)->p2.y = 80;
    (triangles + 1)->p3.x = 380; (triangles + 1)->p3.y = 250;
    (triangles + 2)->p1.x = 80; (triangles + 2)->p1.y = 510;
    (triangles + 2)->p2.x = 380; (triangles + 2)->p2.y = 250;
    (triangles + 2)->p3.x = 400; (triangles + 2)->p3.y = 690;
    (triangles + 3)->p1.x = 380; (triangles + 3)->p1.y = 250;
    (triangles + 3)->p2.x = 400; (triangles + 3)->p2.y = 690;
    (triangles + 3)->p3.x = 550; (triangles + 3)->p3.y = 400;
    (triangles + 4)->p1.x = 380; (triangles + 4)->p1.y = 250;
    (triangles + 4)->p2.x = 500; (triangles + 4)->p2.y = 200;
    (triangles + 4)->p3.x = 170; (triangles + 4)->p3.y = 80;
    (triangles + 5)->p1.x = 500; (triangles + 5)->p1.y = 200;
    (triangles + 5)->p2.x = 380; (triangles + 5)->p2.y = 250;
    (triangles + 5)->p3.x = 550; (triangles + 5)->p3.y = 400;
    (triangles + 6)->p1.x = 80; (triangles + 6)->p1.y = 510;
    (triangles + 6)->p2.x = 100; (triangles + 6)->p2.y = 620;
    (triangles + 6)->p3.x = 400; (triangles + 6)->p3.y = 690;
    (triangles + 7)->p1.x = 400; (triangles + 7)->p1.y = 690;
    (triangles + 7)->p2.x = 550; (triangles + 7)->p2.y = 400;
    (triangles + 7)->p3.x = 550; (triangles + 7)->p3.y = 610;
    (triangles + 8)->p1.x = 660; (triangles + 8)->p1.y = 500;
    (triangles + 8)->p2.x = 550; (triangles + 8)->p2.y = 400;
    (triangles + 8)->p3.x = 550; (triangles + 8)->p3.y = 610;

}
// void randominitialization (triangle* triangles)
// {
//     srand(time(0));
//    (triangles + 0)->p1.x = 30; (triangles + 0)->p1.y = 100;
//    (triangles + 0)->p2.x = 100; (triangles + 0)->p2.y = 30;
//    (triangles + 0)->p3.x = 30; (triangles + 0)->p3.y = 100;

//   for (int i = 1; i < 15; i++)
//    {
//        ((triangles + i)->p1).x = ((triangles + i - 1)->p2).x; ((triangles + i)->p1).y = ((triangles + i - 1)->p2).y;
//        ((triangles + i)->p2).x = ((triangles + i - 1)->p3).x; ((triangles + i)->p2).y = ((triangles + i - 1)->p3).y;
//        ((triangles + i)->p3).x = rand() / 3000000; ((triangles + i)->p3).y = rand() / 3000000; 
//    }
// }


// Drawing the map
void centercalculator(triangle* triangles, int n)
{
    for (int i = 0; i < n; i++)
    {
        (triangles + i)->center.x = 2 * ((triangles + i)->p1.x + (triangles + i)->p2.x + (triangles + i)->p3.x) / 3;
        (triangles + i)->center.y = 2 * ((triangles + i)->p1.y + (triangles + i)->p2.y + (triangles + i)->p3.y) / 3;        
    }
}
void drawcastle (triangle* triangles, int n, SDL_Renderer* renderer)
{
    for (int i = 0; i < n; i++)
    {
        if ((triangles +i)->flag)
            filledCircleColor(renderer, (triangles + i)->center.x, (triangles + i)->center.y, 20, 0xff000099);
        else if ((triangles + i)->background != 0xff808080)
        {
            filledCircleColor(renderer, (triangles + i)->center.x, (triangles + i)->center.y, 20, 0xff994c00);
        }
        else 
            filledCircleColor(renderer, (triangles + i)->center.x, (triangles + i)->center.y, 20, 0xffe0e0e0);
    }
}


void rectinitializer (triangle* triangles, int n)
{
    for (int i = 0; i < n; i++)
    {
        (triangles + i)->number.x = (triangles + i)->center.x;
        (triangles + i)->number.y = (triangles + i)->center.y + 10;
        (triangles + i)->number.w = 50;
        (triangles + i)->number.h = 50;
    }
}


void drawmap(triangle* triangles, SDL_Renderer* renderer)
{
    for (int i = 0; i < 9; i ++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            filledTrigonColor(renderer, 2 * ((triangles + i)->p1).x, 2 * ((triangles + i)->p1).y, 2 * ((triangles + i)->p2).x, 2 * ((triangles + i)->p2).y, 2 * ((triangles + i)->p3).x, 2 * ((triangles + i)->p3).y, (triangles + i)->background);
        thickLineColor(renderer,  2 * ((triangles + i)->p1).x, 2 * ((triangles + i)->p1).y, 2 * ((triangles + i)->p2).x, 2 * ((triangles + i)->p2).y, 7, background);
        thickLineColor(renderer,  2 * ((triangles + i)->p1).x, 2 * ((triangles + i)->p1).y, 2 * ((triangles + i)->p3).x, 2 * ((triangles + i)->p3).y, 7, background);
        thickLineColor(renderer,  2 * ((triangles + i)->p3).x, 2 * ((triangles + i)->p3).y, 2 * ((triangles + i)->p2).x, 2 * ((triangles + i)->p2).y, 7, background);
    }
}



