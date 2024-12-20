#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <sys/time.h>
#include <cstdint>

#include <SDL2/SDL.h>
#include "Util/Vec.h"
#include "Util/Helpers.h"

#include "Objects/Object.h"
#include "Objects/test.h"

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


/* Main gameloop, maintains a semi-fixed timestep */
void main_loop(SDL_Window *window, SDL_Surface *surf, SDL_Surface *back) {
  using namespace std;
  using namespace chrono;

  /* Setup clocks */
  steady_clock::time_point lastTime = steady_clock::now();
  steady_clock::time_point currentTime;

  Test_Obj test;

  while (!window_poll_event()) {
    currentTime = steady_clock::now();
    auto deltaTime = currentTime - lastTime;

    if (deltaTime.count() >= TICK_INTERVAL) {
      Object::update_objects(duration<double>(deltaTime).count());

      lastTime = currentTime;  // Reset the last time
    }

    /* clear screen */
    memset(surf->pixels, 0x00, surf->w * surf->h * surf->format->BytesPerPixel);

    /* draw game */
    Object::render_objects(surf);

    /* render framebuffer and swap buffers */
    SDL_UpdateWindowSurface(window);
    swap_surface(surf, back);

    // Sleep for a short time to prevent busy-waiting
    this_thread::sleep_for(milliseconds(1));
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
    SDL_FreeSurface(back_buff);
    SDL_Quit();

    return EXIT_SUCCESS;
}
