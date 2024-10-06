#include <stdio.h>
#include <SDL2/SDL.h>

const int WIDTH = 640, HEIGHT = 480;

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Surface *surf = NULL;
    SDL_Event e;
    int quit = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialize SDL 2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                              WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to initialize window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    surf = SDL_GetWindowSurface(window);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = 1;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}