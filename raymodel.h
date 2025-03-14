#ifndef RAYMODEL_H
#define RAYMODEL_H

struct Body;
struct LightRay;


/// Function to draw a normal body (circular) onto the the SDL screen  
///
/// @param body The body whose information will be used to draw
/// @param surf The SDL surface to draw on
void drawNormalBody(struct Body body, SDL_Surface* surf)

/// Function to draw a strange body (non-circular) onto the the SDL screen  
///
/// @param body The body whose information will be used to draw
/// @param surf The SDL surface to draw on
void drawStrangeBody(struct Body body, SDL_Surface* surf)

/// Function to draw a naive light rays onto the the SDL screen
///
/// @param lights The array of lightRay structs whose information will be used to draw
/// @param body The body whose information will be used to draw
/// @param surf The SDL surface to draw on
void drawLight(struct LightRay lights, struct Body body, SDL_Surface* surf)

#endif