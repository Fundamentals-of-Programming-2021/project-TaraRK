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
#include "string.h"

void textmaker(SDL_Renderer *renderer, int x, int y, char *text)
{
    TTF_Font *sans = TTF_OpenFont("Sans.ttf", 50);
    SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    SDL_Color black = {0, 0, 0, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(sans, text, black);
    rect->x = x;
    rect->y = y;
    rect->h = surface->h;
    rect->w = surface->w;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    free(rect);
    TTF_CloseFont(sans);
}
void usernametext (SDL_Renderer *renderer, int x, int y, char *text)
{
    TTF_Font *sans = TTF_OpenFont("Sans.ttf", 50);
    SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(sans, text, white);
    rect->x = x;
    rect->y = y;
    rect->h = surface->h;
    rect->w = surface->w;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    free(rect);
    TTF_CloseFont(sans);
}

void getusername(SDL_Renderer * renderer, char* username)
{
    SDL_bool shallExit = SDL_FALSE;
    char character;
    mouse mouse;
    while(shallExit == SDL_FALSE)
    {
        int l = strlen(username);
        SDL_SetRenderDrawColor(renderer, 0x33, 0x00, 0x66, 0xff);
        SDL_RenderClear(renderer);
        usernametext(renderer, 600, 300, username);
        SDL_RenderPresent(renderer);
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
                     break;
                     case SDL_KEYUP:
                            switch(sdlEvent.key.keysym.sym)
                            {
                                  case SDLK_RETURN:
                                  if(l > 0)
                                      return;
                                 break;
                                 case SDLK_SPACE:
                                 character = ' ';
                                 break;

                                case SDLK_UP:
                                 character = '\0';
                                 break;

                                case SDLK_RIGHT:
                                 character = '\0';
                                 break;

                                case SDLK_DOWN:
                                 character = '\0';
                                 break;

                                case SDLK_LEFT:
                                 character = '\0';
                                 break;
                                 case SDLK_BACKSPACE:
                                  character = ' ';
                                  if(l > 1)
                                  username[l - 1] = '\0';
                                 break;
                                 default:
                                       character = sdlEvent.key.keysym.sym;                        
                                 break;

                            }
                            if(l <= 13 && (character >= '0' && character <= '9') ||
                            (character >= 'A' && character <= 'Z') || 
                            (character >= 'a' && character <= 'z') )
                            {
                                username[l] = character;
                                username[l + 1] = '\0';
                            }
                     break;
                }
          } 
    }
}

void sortusernames(char *new_username, player* participants, int n)
{
    FILE* f1;
    FILE* f2;
    FILE* f3;
    f1 = fopen("wholename.txt", "rw");
    f2 = fopen("name.txt", "rw");
    f3 = fopen("score.txt", "rw");

     if (f1 == NULL) 
    {
        printf("File doesn't exist!");
        return ;
    }
    if (f2 == NULL) 
    {
        printf("File doesn't exist!");
        return ;
    }
    if (f3 == NULL) 
    {
        printf("File doesn't exist!");
        return ;
    }
    int total_users1 = 0;
    int total_users2 = 0;
    int total_users3 = 0;
    while (fscanf(f3, "%d", &participants[total_users3].score) != EOF)
    {
      total_users3++;
    }
    fclose(f3);
    while (fscanf(f2, " %s", participants[total_users2].name) != EOF)
    {
      
      total_users2++;
    }
    fclose(f2);
    while (fscanf(f1, " %[^\n]%*c", participants[total_users1].whole_name) != EOF)
    {
      total_users1++;
    }
    fclose(f1);

    int check = 0;
    for(int i = 0; i < total_users1;i++)
    {
      if(strcmp(participants[i].name, new_username)==0)
      {
        participants[i].score += n;
        char old_user[20];
        strcpy(old_user,participants[i].name);
        strcat(old_user," : ");
        char str[10];
        sprintf(str, "%d", participants[i].score);
        strcat(old_user,str);
        strcpy(participants[i].whole_name,old_user);
        check = 1;
        break;
      }
    }
    if(check == 0)
    {
      strcpy(participants[total_users1].name,new_username);
      
      participants[total_users1].score = n;
      strcat(new_username," : ");
      char str[10];
      sprintf(str, "%d", n);
      strcat(new_username,str);
      strcpy(participants[total_users1].whole_name,new_username);
      total_users1++;
    }

    f1 = fopen("wholename.txt", "w");
    f2 = fopen("name.txt", "w");
    f3 = fopen("score.txt", "w");

   bubbleSort(participants,total_users1);
    for (int i = 0; i < total_users1; i++) {
  
        fprintf(f1, "%s\n", participants[i].whole_name);
        fprintf(f2, "%s\n", participants[i].name);
        fprintf(f3, "%d\n", participants[i].score);
    }

        fclose(f2);
        fclose(f1);
        fclose(f3);
}
void bubbleSort(player participants[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
  
       for (j = 0; j < n-i-1; j++) 
           if (participants[j].score < participants[j+1].score)
              swap(&participants[j], &participants[j+1]);
}
void swap(player *xp, player *yp)
{
    player temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void rankings(SDL_Renderer * sdlRenderer,const int SCREEN_WIDTH,const int SCREEN_HEIGHT)
{
    SDL_bool shallExit = SDL_FALSE;
    while(shallExit == SDL_FALSE)
    {
        char names[20];
        int totalusers = 0;
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);
        FILE* f1;
        f1 = fopen("wholename.txt", "r");
        FILE* f2;
        f2 = fopen("wholename.txt", "r");
        while (fscanf(f1, "%[^\n]%*c", names) != EOF)
        {
            totalusers++;
        }
        fclose(f1);
        int i = 0;
        int height = 45;
        while (fscanf(f2, "%[^\n]%*c", names) != EOF && (i < totalusers && i < 5))
        {
            textmaker(sdlRenderer, 330 , height + 35, names);
            height += 110;
            i++;
        }
        fclose(f2);
        SDL_RenderPresent(sdlRenderer); 
        SDL_Delay(1000/60);
        SDL_Event sdlEvent;
        while(SDL_PollEvent(&sdlEvent))
        {
            switch(sdlEvent.type)
            {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }
    }
}
void load_image(SDL_Renderer * sdlRenderer,char * string,int x0,int y0,int w0,int h0)
{
   SDL_Surface * image = IMG_Load(string);
   if(image == NULL)
   {
        fprintf(stderr, "error: image not found\n");
        exit(EXIT_FAILURE);
   }
   SDL_Texture * txt = SDL_CreateTextureFromSurface(sdlRenderer,image);
   SDL_FreeSurface(image);
   image = NULL;
   SDL_Rect rect2 = {.x = x0,.y = y0,.w = w0,.h = h0};
   SDL_RenderCopy(sdlRenderer,txt,NULL,&rect2);
   SDL_DestroyTexture(txt);

}
