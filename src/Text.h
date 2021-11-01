
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

class Text
{
    public:
        int w,h;
        Text(){ Free(); }

        Text(SDL_Renderer* renderer,TTF_Font* font, SDL_Color color, const char* text); 

        void Draw(SDL_Renderer* renderer,int x,int y);

        void Free();

        SDL_Color color;
        TTF_Font* font;
    private:
        SDL_Texture* texture = nullptr;

};
