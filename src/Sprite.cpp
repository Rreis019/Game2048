#include "Sprite.h"
#include <stdio.h>

Sprite::Sprite(SDL_Renderer* renderer,const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    if(surface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        width = surface->w;
        height = surface->h;

        if(texture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }
}

void Sprite::Draw(SDL_Renderer* renderer,int x, int y)
{
    //draw sprite
    SDL_Rect rect = {x,y,width,height};
    SDL_RenderCopy(renderer, this->texture, NULL, &rect);
}
