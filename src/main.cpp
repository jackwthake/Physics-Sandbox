#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <sys/time.h>
#include <cstdint>

#include <SDL2/SDL.h>
#include "Util/Vec.h"

const int WIDTH = 640, HEIGHT = 480;
const int TICKS_PER_SECOND = 5;
const int TICK_INTERVAL = 1000 / TICKS_PER_SECOND;  // milliseconds per tick

/* Physics Constants */
const double G = 9.81;
const double Pixel_To_Meter = 32; // 1 meter = 32 pixels
const int Floor_Height = 15; // 15 meters from top left origin

/* Basic physics object, has poisition, bounds, and something to modulate position. */
struct Object {
  Vector2 position = { 4, 0 }, velocity = { 0, 0 }, acceleration = { 0, 0 };
  Vector2 bounds = { 1, 1 }; // 1 meter x 1 meter

  double mass = 1; // 1kg
  bool grounded = false;
};


/* Helper function to set one pixel's color in the framebuffer */
static void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                                    + y * surface->pitch
                                                    + x * surface->format->BytesPerPixel);
  *target_pixel = pixel;
}


/* Helper function to draw rect at specified x, y of w, h */
static void draw_rect(SDL_Surface *surf, Vector2 &pos, Vector2 &bounds, Uint32 pixel) {
    int i, j;
    for (i = pos.y * Pixel_To_Meter; i < pos.y * Pixel_To_Meter + bounds.y * Pixel_To_Meter; ++i) {
        for (j = pos.x * Pixel_To_Meter; j < pos.x * Pixel_To_Meter + bounds.x * Pixel_To_Meter; ++j) {
            if (i <= HEIGHT && j <= WIDTH && i >= 0 && j >= 0)
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

/* Apply a force to an objects acceleration vetor */
void apply_force(Object &obj, Vector2 &F) {
    obj.acceleration += F;
}

/* Update Object */
void update_object(Object &obj, double dt) {
  if (obj.position.y + obj.bounds.y < Floor_Height)
    obj.acceleration.y = obj.mass * G * dt;

  if (obj.position.y + obj.bounds.y >= Floor_Height) {
    obj.acceleration.y = 0;
    obj.velocity.y = 0;
    obj.position.y = Floor_Height - obj.bounds.y;

    obj.grounded = true;
  }

  const uint8_t *key_state = SDL_GetKeyboardState(NULL);
  if (key_state[SDL_SCANCODE_SPACE] && obj.grounded) {
    Vector2 F = { 0.0, -5 * obj.mass * G * dt }; // Apply an upward force to the object
    apply_force(obj, F);

    obj.grounded = false;
  }

  /* update position */
  obj.velocity += obj.acceleration;
  obj.position += obj.velocity;

  std::cout << "position: " << obj.position << "\nvelocity: " << obj.velocity << "\nacceleration: " << obj.acceleration << std::endl;
}


void render_object(SDL_Surface *surf, Object &obj) {
  draw_rect(surf, obj.position, obj.bounds, 0xFFFFFF);
}

void main_loop(SDL_Window *window, SDL_Surface *surf, SDL_Surface *back) {
  using namespace std;
  using namespace chrono;

  steady_clock::time_point lastTime = steady_clock::now();
  steady_clock::time_point currentTime;

  Object obj;

  while (!window_poll_event()) {
    currentTime = steady_clock::now();
    auto deltaTime = currentTime - lastTime;

    if (deltaTime.count() >= TICK_INTERVAL) {
      update_object(obj, duration<double>(deltaTime).count());

      lastTime = currentTime;  // Reset the last time
    }

    /* clear screen */
    memset(surf->pixels, 0x00, surf->w * surf->h * surf->format->BytesPerPixel);

    /* draw game */
    render_object(surf, obj);

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
