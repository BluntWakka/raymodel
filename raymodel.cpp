#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

using namespace std;

//Defines for easy access and modification of window elements
#define SDL_W 1000
#define SDL_L 1000
#define BODY_COLOR FFFFFF
#define LIGHT_COLOR FFAE42
#define NUM_LIGHT 20

// Current approach is to take light from a source and have it reflect once upon coming into "contact" with a surface 
// (removed "incidence" variants out of redundancy)
struct LightRay
{
    double x_origin;
    double y_origin;
    double origin_angle;
};

// Struct to hold locational and size information on celestial bodies
//Type 0 == Normal, Type 1 == Strange
struct Body
{
    double x;
    double y;
    double radius;
    int type;
};

int main(int argc,char **)
{
    //Check for strange or normal body
    int type = 0;
    if (argc == 1 && argv[0][0]=='s')
    {
        type=1;
    }
    
    //Attempt init of video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("SDL init error: %s", SDL_GetError());
        return 1;
    }

    //Attempt creation of window for SDL
    SDL_Window * window = SDL_CreateWindow("Celestial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_W, SDL_L, 0);
    if (!window) 
    {
        SDL_Log("Window failed to create: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    //Intitialize lights
    struct LightRay lights[NUM_LIGHT];
    double angle = 0;
    for(int i =0; i<NUM_LIGHT; i++)
    {
        angle = ((double)i / NUM_LIGHT) * M_PI * 2;
        struct LightRay light = {body.x,body.y,angle};
        lights[i]=light;
    }

    printf("Testing End\n");
}

void drawNormalBody(struct Body body, SDL_Surface* surf)
{
    //Pre-defined values for memory access efficiency due to very high repetition
    double rsqr = body.radius * body.radius;
    double min_x = body.x - body.radius;
    double max_x = body.x + body.radius;

    double min_y = body.y - body.radius;
    double max_y = body.y + body.radius;

    //Nested loops for rendering the body
    for (double x = min_x; x <= max_x; x++)
    {
        for (double y = min_y; y <= max_y; y++)
        {
            double dsqr = ((x-body.x)*(x-body.x)) + ((y-body.y)*(y-body.y))
            if (dsqr < rsqr)
            {
                SDL_Rect pix = (SDL_Rect){x,y,1,1};
                SDL_FillRect(surf, &pix, BODY_COLOR);
            }
        }
    }
}

void drawLight(struct LightRay lights[NUM_LIGHT], struct Body body, SDL_Surface* surf)
{
    double rsqr = body.radius * body.radius;

    //Draw each light individually until it reaches a point of collision or OOB (Out of bounds)
    for (int i = 0; i < NUM_LIGHT; i++)
    {
        int oob = 0;
        int collide = 0;
        struct curLight = lights[i]

        double xCurLoc = light.x_origin;
        double yCurLoc = light.y_origin;
        double mov = 1

        while(!(collide==2) && !oob)
        {
            xCurLoc+=mov*cos(light.origin_angle);
            yCurLoc+=mov*sin(light.origin_angle);

            SDL_Rect pix = (SDL_Rect){xCurLoc,yCurLoc,1,1};
            SDL_FillRect(surf, &pix, LIGHT_COLOR);

            if(xCurLoc<0 || xCurLoc>SDL_W || yCurLoc<0 || yCurLoc>SDL_L)
            {
                oob=1;
            }



        }
    }
}

