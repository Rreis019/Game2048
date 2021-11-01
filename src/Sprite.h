#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

//create class sprite
class Sprite
{
    public:
        Sprite(){}
        Sprite(SDL_Renderer* renderer,const char* path);
        Sprite(SDL_Renderer* renderer,const char* path, int TransparentR, int TransparentG, int TransparentB);

        void Draw(SDL_Renderer* renderer,int x, int y);
        void Free(){
            if(texture != NULL)
            {
                SDL_DestroyTexture(texture);
                printf("Sprite destroyed\n");
            }
        }
        SDL_Texture* texture = NULL;
    private:

        int width,height;
};


