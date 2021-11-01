#include "Clock.h"
#include <SDL2/SDL.h>
#include <stdio.h>
void Clock::LimitFps(int fps)
{
     //Limit fps
    int frameTicks = SDL_GetTicks() - lastFrameTicks;
    if(frameTicks < (1000 / fps))
    {
        SDL_Delay((1000 / fps) - frameTicks);
    }
    //get fps
    Currentfps = 1000 / (SDL_GetTicks() - lastFrameTicks);
    lastFrameTicks = SDL_GetTicks();
}

