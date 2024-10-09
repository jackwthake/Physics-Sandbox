#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#include <SDL2/SDL.h>

const int WIDTH = 640, HEIGHT = 480;
const int dt = 50; /* tick every 20ms */

/* get timestep in microseconds */
long int get_timestamp(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_usec;
}


/* Helper function to set one pixel's color in the framebuffer */
static void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                                    + y * surface->pitch
                                                    + x * surface->format->BytesPerPixel);
  *target_pixel = pixel;
}


/* Helper function to draw rect at specified x, y of w, h */
static void draw_rect(SDL_Surface *surf, int x, int y, int w, int h, Uint32 pixel) {
    int i, j;
    for (i = y; i < y + h; ++i) {
        for (j = x; j < x + w; ++j) {
            set_pixel(surf, j, i, pixel);
        }
    } 
}

/* Helper. polls window for new input  */
static int window_poll_event(void) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            return 1;
    }

    return 0;
}


/* Swap back and front buffers */
static void swap_surface(SDL_Surface *x, SDL_Surface *y) {
    SDL_Surface *temp = x;
    x = y;
    y = temp;
}


float x = 64;
/* Main program loop */
void main_loop(SDL_Window *window, SDL_Surface *surf, SDL_Surface *back) {
    int quit = 0;

    Uint32 current_time = SDL_GetTicks();

    while (!quit) {
        Uint32 new_time = SDL_GetTicks();
        Uint32 frame_time = new_time - current_time;
        current_time = new_time;

        while (frame_time > 0.0) {
            float delta = fmin(frame_time, dt);

            /* Update and poll input */
            quit = window_poll_event();
            x += 20 * (delta / 1000);

            printf("frame_time = %ims\n", frame_time);
            frame_time -= delta;
        }

        memset(surf->pixels, 0x00, surf->w * surf->h * surf->format->BytesPerPixel);

        draw_rect(surf, x, 32, 32, 32, SDL_MapRGB(surf->format, 255, 0, 0));

        SDL_UpdateWindowSurface(window);
        swap_surface(surf, back);
    }
}


int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Surface *surf = NULL, *back_buff;

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

    back_buff = SDL_DuplicateSurface(surf);

    /* Main game loop */
    main_loop(window, surf, back_buff);

    /* Cleanup */
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}