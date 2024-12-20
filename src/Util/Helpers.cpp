#include "Helpers.h"

/* Helper function to set one pixel's color in the framebuffer */
static void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                                    + y * surface->pitch
                                                    + x * surface->format->BytesPerPixel);
  *target_pixel = pixel;
}


static uint32_t rgbToInt(SDL_Color &c) {
    // Shift the red, green, and blue values into their correct positions in the 32-bit integer
    uint32_t color = 0;
    color |= (c.r << 16);  // Red goes into the 16-23 bits
    color |= (c.g << 8);   // Green goes into the 8-15 bits
    color |= c.b;          // Blue goes into the 0-7 bits
    return color;
}


/* Draw a rectangle of a given size and color at a given position */
void draw_rect(SDL_Surface *surf, Vector2 &pos, Vector2 &bounds, SDL_Color &pixel) {
    int i, j;
    for (i = pos.y * Pixel_To_Meter; i < pos.y * Pixel_To_Meter + bounds.y * Pixel_To_Meter; ++i) {
        for (j = pos.x * Pixel_To_Meter; j < pos.x * Pixel_To_Meter + bounds.x * Pixel_To_Meter; ++j) {
            if (i <= HEIGHT && j <= WIDTH && i >= 0 && j >= 0)
              set_pixel(surf, j, i, rgbToInt(pixel));
        }
    }
}