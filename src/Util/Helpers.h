#ifndef HELPERS_H
#define HELPERS_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include "Vec.h"

/* General Constants */
const int WIDTH = 640, HEIGHT = 480;
const int TICKS_PER_SECOND = 5;
const int TICK_INTERVAL = 1000 / TICKS_PER_SECOND;  // milliseconds per tick

/* Physics Constants */
const double G = 9.81;
const double Pixel_To_Meter = 32; // 1 meter = 32 pixels
const int Floor_Height = 15; // 15 meters from top left origin

/* Helper function to draw rect at specified x, y of w, h */
void draw_rect(SDL_Surface *surf, Vector2 &pos, Vector2 &bounds, SDL_Color &col);

#endif