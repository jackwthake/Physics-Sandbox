#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

const int WIDTH = 640, HEIGHT = 480;

/* Helper function to set one pixel's color in the framebuffer */
static void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                                    + y * surface->pitch
                                                    + x * surface->format->BytesPerPixel);
  *target_pixel = pixel;
}

/* Main program loop c */
void main_loop(SDL_Window *window, SDL_Surface *surf) {
    SDL_Event e;
    int quit = 0;
    float acc = 0.f;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = 1;
        }

        acc += 0.01;

        /* Clear Screen buffer*/
        memset(surf->pixels, 0x00, surf->w * surf->h * surf->format->BytesPerPixel);

        /* draw a rectangle moving on the window*/
        int x, y;
        for (y = 0; y < 64; ++y) {
            for (x = 0; x < 64; ++x) {
                set_pixel(surf, (WIDTH / 2) + x + (cos(acc) * 100), (HEIGHT / 2) + y + (sin(acc) * 100), SDL_MapRGB(surf->format, 255, 0, 0));
            }
        }

        /* Render updated framebuffer */
        SDL_UpdateWindowSurface(window);
    }
}


int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Surface *surf = NULL;

    /* Init SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialize SDL 2: %s\n", SDL_GetError());
        return -1;
    }

    /* Initialize graphics window*/
    window = SDL_CreateWindow("hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                              WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to initialize window: %s\n", SDL_GetError());
        return -1;
    }

    /* Initialize screenbuffer */
    surf = SDL_GetWindowSurface(window);
    if (!surf) {
        printf("Failed to initialize window surface: %s\n", SDL_GetError());
        return -1;
    }

    /* Main game loop */
    main_loop(window, surf);

    /* Cleanup */
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}