#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

using namespace std;

//Defines for easy access and modification of window elements
#define SDL_W 1000
#define SDL_L 1000
#define STOPPER_COLOR 0xFFFFFF
#define BACKGROUND_COLOR 0x000000
#define LIGHT_COLOR 0xFFAE42
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

void drawNormalBody(struct Body body, SDL_Surface* surf, Uint32 color)
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
            double dsqr = ((x-body.x)*(x-body.x)) + ((y-body.y)*(y-body.y));
            if (dsqr < rsqr)
            {
                SDL_Rect pix = (SDL_Rect){x,y,1,1};
                SDL_FillRect(surf, &pix, color);
            }
        }
    }
}

void drawStrangeBody(struct Body body, SDL_Surface* surf, Uint32 color)
{
    //Pre-defined values for memory access efficiency due to very high repetition
    double rsqr = body.radius * body.radius;
    double min_x = body.x - body.radius;
    double max_x = 2*(body.x + body.radius);

    double min_y = body.y - body.radius;
    double max_y = body.y + body.radius;

    //Nested loops for rendering the body
    for (double x = min_x; x <= max_x; x++)
    {
        for (double y = min_y; y <= max_y; y++)
        {
            double dsqr = ((x-body.x)*(x-body.x)) + ((y-body.y)*(y-body.y));
            if (dsqr < rsqr)
            {
                SDL_Rect pix = (SDL_Rect){x,y,1,1};
                SDL_FillRect(surf, &pix, color);
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
        struct LightRay curLight = lights[i];
        int t = body.type;

        double xCurLoc = curLight.x_origin;
        double yCurLoc = curLight.y_origin;
        double mov = 1;

        while(!collide && !oob)
        {
            xCurLoc+=mov*cos(curLight.origin_angle);
            yCurLoc+=mov*sin(curLight.origin_angle);

            SDL_Rect pix = (SDL_Rect){xCurLoc,yCurLoc,1,1};
            SDL_FillRect(surf, &pix, LIGHT_COLOR);

            if(xCurLoc<0 || xCurLoc>SDL_W || yCurLoc<0 || yCurLoc>SDL_L)
            {
                oob=1;
            }

            if(t)
            {
                //Strange body code
                double dsqr = (2*(xCurLoc-body.x)*(xCurLoc-body.x)) + ((yCurLoc-body.y)*(yCurLoc-body.y));
                if (dsqr<rsqr)
                {
                    break;
                }
            }
            else
            {
                //Normal body code
                double dsqr = ((xCurLoc-body.x)*(xCurLoc-body.x)) + ((yCurLoc-body.y)*(yCurLoc-body.y));
                if (dsqr<rsqr)
                {
                    break;
                }
            }

        }
    }
}

int main(int argc, char ** argv)
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

    SDL_Surface* surf = SDL_GetWindowSurface(window);
    struct Body source = {350,350,50,0};
    struct Body stopper = {500,500,200,type}; 
    struct LightRay lights[NUM_LIGHT];
    SDL_Rect reset = {0,0,SDL_W,SDL_L};
    double angle = 0;

    //Initialize the light array
    for(int i =0; i<NUM_LIGHT; i++)
    {
        angle = ((double)i / NUM_LIGHT) * M_PI * 2;
        struct LightRay light = {source.x,source.y,angle};
        lights[i]=light;
    }

    int running = 1;
    SDL_Event event;

    //Control direction of stopper object that is moving
    double xMov = 1;
    double yMov = 1;
    
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running=0;
            }
            if(event.type == SDL_MOUSEMOTION && event.motion.state != 0)
            {
                source.x = event.motion.x;
                source.y = event.motion.y;
                for(int i =0; i<NUM_LIGHT; i++)
                {
                    angle = ((double)i / NUM_LIGHT) * M_PI * 2;
                    struct LightRay light = {source.x,source.y,angle};
                    lights[i]=light;
                }
            }
        }

        SDL_FillRect(surf,&reset,BACKGROUND_COLOR);
        drawLight(lights,stopper,surf);
        drawNormalBody(source,surf, LIGHT_COLOR);
        if(type)
        {
            drawStrangeBody(stopper,surf, STOPPER_COLOR);
        }
        else
        {
            drawNormalBody(stopper,surf, STOPPER_COLOR);
        }

        stopper.x += xMov;
        stopper.y += yMov;

        if (stopper.y - stopper.radius < 0 || stopper.y + stopper.radius > SDL_L)
        {
            yMov= -yMov;
        }

        if (stopper.x - stopper.radius < 0 || stopper.x + stopper.radius > SDL_W)
        {
            xMov= -xMov;
        }

        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }

}

