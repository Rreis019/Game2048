
#include "Text.h"

Text::Text(SDL_Renderer* renderer,TTF_Font* font, SDL_Color color, const char* text)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    this->w = surface->w;
    this->h = surface->h;

    SDL_FreeSurface(surface);

    this->color = color;
    this->font = font;
} 

void Text::Draw(SDL_Renderer* renderer,int x,int y)
{
    if (texture == nullptr)
        return;


    SDL_Rect rect = {x,y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Text::Free()
{
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
