#include "Helpers.h"

/* Helper function to set one pixel's color in the framebuffer */
static void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                                    + y * surface->pitch
                                                    + x * surface->format->BytesPerPixel);
  *target_pixel = pixel;
}

/* Draw a rectangle of a given size and color at a given position */
void draw_rect(SDL_Surface *surf, Vector2 &pos, Vector2 &bounds, Uint32 pixel) {
    int i, j;
    for (i = pos.y * Pixel_To_Meter; i < pos.y * Pixel_To_Meter + bounds.y * Pixel_To_Meter; ++i) {
        for (j = pos.x * Pixel_To_Meter; j < pos.x * Pixel_To_Meter + bounds.x * Pixel_To_Meter; ++j) {
            if (i <= HEIGHT && j <= WIDTH && i >= 0 && j >= 0)
              set_pixel(surf, j, i, pixel);
        }
    }
}