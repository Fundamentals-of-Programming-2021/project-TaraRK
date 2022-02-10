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
const int FPS = 55;
Uint32 background = 0xffe0e0e0;
SDL_Color black = {0, 0, 0, 255};
time_t t2;
void randoms ()
{
    srand((unsigned)time(&t2));
}
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
    for (int i = 0; i < n; i++)
    {
        inttostr((triangles + i)->soldiernum, (triangles + i)->numstr);
        (triangles + i)->surfaceMessage = TTF_RenderText_Solid(sans, (triangles + i)->numstr, black);
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

//Potion Functions

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
        potion->flag = 0;
        switch (potion->type)
        {
            case 1 :
                potion->countmax = 300;
                potion->stopattack = 0;
                break;
            case 2 :
                potion->countmax = 500;
                break;
            case 3 :
                potion->countmax = 250;
                break;
            case 4 :
                potion->countmax = 400;
                break;
        }
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
}
void potiontest(potion* potion, SDL_Renderer* renderer)
{
    IMG_Init(IMG_INIT_JPG);
    SDL_Surface* surface = IMG_Load("/home/tara/Desktop/project/1.jpg");
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, text, NULL, &potion->rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(text);
    IMG_Quit();
}
int hitpotion (soldier* soldiers, potion* potion)
{
    if (soldiers->x >= potion->rect.x && (soldiers->x <= potion->rect.x + potion->rect.w) 
        && soldiers->y >= potion->rect.y && (soldiers->y <= potion->rect.y + potion->rect.h) )
        return 1;
    else 
        return 0;
}

void potiontime(SDL_Renderer* renderer, potion* potion)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x66, 0x33, 0xff);
    potion->time.x = 750;
    potion->time.y = 60;
    potion->time.h = 50;
    double temp = (double)(potion->counter) / (double)(potion->countmax);
    potion->time.w = temp * 600;
    SDL_RenderFillRect(renderer, &(potion->time));
    if (potion->type == 1)
    {
        potion->stopattack = 1;
    }    
}
void potioninit(potion* potion)
{
    switch (potion->type)
    {
        case 1 : // stops from moving
            potion->stopattack = 1;
            break;
        case 2 : // increases soldier speed
            if (potion->activeforopp) {potion->rp = 1.5;}
            else { potion->r = 1.5;}
            break;
        case 3 : //increases soldier creation rate
            potion->rgameprogress = 10;
            break;
        case 4 : // stops from attacking
            potion->attack = 0;
            break;

    }
}
// void potiontext (potion* potion, SDL_Renderer* renderer)
// {
//     sw
// }
void potionquit (potion* potion)
{
    switch (potion->type)
    {
        case 1 : // stops from moving
            potion->stopattack = 0;
            break;
        case 2 :
            potion->r = 1;
            potion->rp = 1;
            break;
        case 3 :
            potion->rgameprogress = 15;
            break;
        case 4 :
            potion->attack = 1;
            break;
    }
}
void potiontext(potion* potion, SDL_Renderer* renderer)
{
    SDL_Surface* surface;
    SDL_Texture* text;
    potion->textbox.x = 750;
    potion->textbox.y = 130;
    potion->textbox.h = 50;
    potion->textbox.w = 300;
    TTF_Font *sans = TTF_OpenFont("/home/tara/Desktop/project/Sans.ttf", 20);
    if (potion->activeforopp)
    {
        switch (potion->type)
        {
            case 1:
                surface = TTF_RenderText_Solid(sans, "Movement block potion activated for opponent", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 2:
                surface = TTF_RenderText_Solid(sans, "Spead raise potion activated for opponent", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 3:
                surface = TTF_RenderText_Solid(sans, "Faster soldier creation activated for opponent", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 4:
                surface = TTF_RenderText_Solid(sans, "Attack block potion activated for opponent", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
        }
    }
    else 
    {
        switch (potion->type)
        {
            case 1:
                surface = TTF_RenderText_Solid(sans, "Movement block potion activated for player", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 2:
                surface = TTF_RenderText_Solid(sans, "Spead raise potion activated for player", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 3:
                surface = TTF_RenderText_Solid(sans, "Faster soldier creation activated for player", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
            case 4:
                surface = TTF_RenderText_Solid(sans, "Attack block potion activated for player", black);
                text = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, text, NULL, &(potion->textbox));
                break;
        }
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(text);
    TTF_CloseFont(sans);
}


