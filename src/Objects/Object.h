#ifndef OBJECT_H
#define OBJECT_H

#include "../Util/Vec.h"

#include <SDL2/SDL_pixels.h> /* SDL_Color struct */

class Object {
public:
  Object(void);
  Object(Vector2 &position, Vector2 &bounds, double mass, SDL_Color col);
  Object(const Object &copy);

  virtual void update(double delta) = 0;
  void render(struct SDL_Surface *surf);

  void apply_force(Vector2 &F);

  static void update_objects(double dt);
  static void render_objects(SDL_Surface *s);

  static bool add_object(Object *obj, std::string &tag);

  bool operator==(const unsigned id);
protected:
  Vector2 position, velocity, acceleration;
  Vector2 bounds;

  double mass;
  bool grounded;
  unsigned id;
  SDL_Color color;
  std::string tag;
};

#endif