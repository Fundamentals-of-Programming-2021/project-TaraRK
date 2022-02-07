#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#define true 1;
Uint32 background = 0xffe0e0e0;
typedef struct triangle
{
    SDL_Point p1, p2, p3;
    SDL_Point center;
    int soldiernum;
    Uint32 background;
    SDL_Rect number;
    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;
    char numstr [5];
    long long int counter;
    int flag;
} triangle;
// typedef struct ellipse
// {
//     Sint16 x;
//     Sint16 y;
//     Sint16 rx;
//     Sint16 ry;

// }ellipse;
// ellipse pause;
// pause.x = 1200;
// pause.y = 300;
// pause.rx = 70;
// pause.ry = 40l
// void pausebutton (ellipse, SDL_Renderer* renderer)
// {
//     filledEllipseColor(renderer, )
// }
int timestamp (SDL_Event* event)
{
    switch (event->type)
    {
        case (SDL_MOUSEBUTTONDOWN || SDL_MOUSEBUTTONUP ):
            return (event->button.timestamp);
    }
}
void initialize(triangle* triangles)
{
    for (int i = 0; i < 9; i ++)
    {
        (triangles + i)->flag = 0;
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
void drawmap(triangle* triangles, SDL_Renderer* renderer)
{
    for (int i = 0; i < 9; i ++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        if ((triangles +i)->flag)
            filledTrigonColor(renderer, 2 * ((triangles + i)->p1).x, 2 * ((triangles + i)->p1).y, 2 * ((triangles + i)->p2).x, 2 * ((triangles + i)->p2).y, 2 * ((triangles + i)->p3).x, 2 * ((triangles + i)->p3).y, (triangles + i)->background);
        else if (i % 3 == 2)
            filledTrigonColor(renderer, 2 * ((triangles + i)->p1).x, 2 * ((triangles + i)->p1).y, 2 * ((triangles + i)->p2).x, 2 * ((triangles + i)->p2).y, 2 * ((triangles + i)->p3).x, 2 * ((triangles + i)->p3).y, (triangles + i)->background);
        else
            filledTrigonColor(renderer, 2 * ((triangles + i)->p1).x, 2 * ((triangles + i)->p1).y, 2 * ((triangles + i)->p2).x, 2 * ((triangles + i)->p2).y, 2 * ((triangles + i)->p3).x, 2 * ((triangles + i)->p3).y, (triangles + i)->background);
        thickLineColor(renderer,  2 * ((triangles + i)->p1).x, 2 * ((triangles + i)->p1).y, 2 * ((triangles + i)->p2).x, 2 * ((triangles + i)->p2).y, 7, background);
        thickLineColor(renderer,  2 * ((triangles + i)->p1).x, 2 * ((triangles + i)->p1).y, 2 * ((triangles + i)->p3).x, 2 * ((triangles + i)->p3).y, 7, background);
        thickLineColor(renderer,  2 * ((triangles + i)->p3).x, 2 * ((triangles + i)->p3).y, 2 * ((triangles + i)->p2).x, 2 * ((triangles + i)->p2).y, 7, background);
    }
}
