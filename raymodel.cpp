#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

using namespace std;

//Defines for easy access and modification of window elements
#define SDL_W 1000
#define SDL_L 1000

// Current approach is to take light from a source and have it reflect once upon coming into "contact" with a surface
struct lightRay
{
    double x_origin;
    double y_origin;
    double x_incidence;
    double y_incidence;
    double origin_angle;
    double incidence_angle;
};

// Struct to hold locational and size information on celestial bodies
struct body
{
    double x;
    double y;
    double radius;
};

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("SDL init error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window * window = SDL_CreateWindow("Celestial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_W, SDL_L, 0);
    if (!window) 
    {
        SDL_Log("Window failed to create: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
}