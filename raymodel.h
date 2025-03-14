#ifndef RAYMODEL_H
#define RAYMODEL_H

struct Body;
struct LightRay;


/// Function to draw a normal body (circular) onto the the SDL screen  
///
/// @param body The body whose information will be used to draw
/// @param surf The SDL surface to draw on
/// @param color The color that should be used to draw the body
void drawNormalBody(struct Body body, SDL_Surface* surf, Uint32 color)

/// Function to draw a strange body (non-circular) onto the the SDL screen  
///
/// @param body The body whose information will be used to draw
/// @param surf The SDL surface to draw on
/// @param color The color that should be used to draw the body
void drawStrangeBody(struct Body body, SDL_Surface* surf, Unit32 color)

/// Function to draw a naive light rays onto the the SDL screen
///
/// @param lights The array of lightRay structs whose information will be used to draw
/// @param body The body whose information will be used to draw and understand whre a collision occurs
/// @param surf The SDL surface to draw on
void drawLight(struct LightRay lights, struct Body body, SDL_Surface* surf)

#endif