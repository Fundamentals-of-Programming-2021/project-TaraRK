#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define true 1;
const int FPS = 50;
Uint32 background = 0xffe0e0e0;
SDL_Color black = {0, 0, 0, 255};
time_t t2;
void randoms ()
{
    srand((unsigned)time(&t2));
}
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

typedef struct soldier 
{
    Sint16 x;
    Sint16 y;
    Sint16 r;
    Uint32 color;
}soldier;

typedef struct potion
{
    SDL_Rect rect;
    int flag;
    int type;
} potion;
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

void textgenerator(triangle* triangles, SDL_Renderer* renderer, int n)
{
    TTF_Font *sans = TTF_OpenFont("/home/tara/Desktop/project/Sans.ttf", 20);
    // SDL_Surface* surface;
    // SDL_Texture* texture;
    for (int i = 0; i < n; i++)
    {
        inttostr((triangles + i)->soldiernum, (triangles + i)->numstr);
        // SDL_Surface* surface;
        // SDL_Texture* texture;
        (triangles + i)->surfaceMessage = TTF_RenderText_Solid(sans, (triangles + i)->numstr, black);
        (triangles + i)->Message = SDL_CreateTextureFromSurface(renderer, (triangles + i)->surfaceMessage);
        // surface = TTF_RenderText_Solid(sans, (triangles + i)->numstr, black);
        // texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, (triangles + i)->Message, NULL, &((triangles +i)->number));
        SDL_FreeSurface((triangles + i)->surfaceMessage);
        SDL_DestroyTexture((triangles + i)->Message);
        // SDL_DestroyTexture(texture);
        // SDL_FreeSurface(surface);
    }
    // SDL_DestroyTexture(texture);
    // SDL_FreeSurface(surface);
    TTF_CloseFont(sans);
//    TTF_Quit(); 
}





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
// Game functions
void gameprogress (triangle* triangles, int n)
{
    for (int i = 0; i < n; i++)
        {
            if ( (triangles + i)->background != 0xff808080)
            {
                if ( (triangles + i)->background != 0xff9999ff && (triangles + i)->background != 0xffffcc99 )
                    (triangles + i)->background += 0x01000000;
                if ((triangles + i)->soldiernum < 50)
                {
                    (triangles + i)->counter ++;
                    (triangles + i)->soldiernum = (triangles + i)->counter / 15;
                }                
            }         
        }
}
void opponentplay(triangle* triangles, SDL_Renderer* sdlRenderer)
{
    int a = rand();
    if (a % 50 == 0 )
        {
            int* opsrc = (int*)malloc(sizeof(int));
            *opsrc = 0;
            while ( (triangles + *opsrc)->flag || (triangles + *opsrc)->background == 0xff808080 )
            {
                *opsrc = rand() % 9;
            }
            int* opdest = (int*)malloc(sizeof(int));
            *opdest = rand() % 9;
        //    soldier* opsoldiers = (soldier*)malloc(sizeof(soldier) * (triangles + *opsrc)->soldiernum);
            if ((triangles + *opsrc)->soldiernum != 0)
            {
            soldier* opsoldiers = (soldier*)malloc(sizeof(soldier) * 200);
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
        }
}

//Potion Functions
void potioncoordinator (potion* potion)
{
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
            surface = IMG_Load("/home/tara/Desktop/project/1.jpg");
            break;
        case 2:
            surface = IMG_Load("/home/tara/Desktop/project/2.jpg");
            break;
        case 3:
            surface = IMG_Load("/home/tara/Desktop/project/3.jpg");
            break;
        case 4:
            surface = IMG_Load("/home/tara/Desktop/project/4.jpg");
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
    }
}