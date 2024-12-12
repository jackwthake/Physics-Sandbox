#include "Object.h"

#include <list>
#include <SDL2/SDL.h>

#include "Util/Helpers.h"

static std::list<Object *> objects;
static unsigned int _id = 0;

/* Constructor */
Object::Object(Vector2 &position, Vector2 &bounds, double mass, SDL_Color col) {
  this->position = position;
  this->bounds = bounds;

  this->velocity = Vector2();
  this->acceleration = Vector2();
  this->mass = mass;

  this->grounded = false;
  this->color = col;
  this->id = _id++;
}


/* Copy constructor */
Object::Object(const Object &copy) {
this->position = copy.position;
  this->bounds = copy.bounds;

  this->velocity = copy.velocity;
  this->acceleration = copy.acceleration;
  this->mass = copy.mass;

  this->grounded = copy.grounded;
  this->color = copy.color;
  this->id = copy.id; // should it get the same id? or should a new one be used...
}


/* Render an individual object */
void Object::render(SDL_Surface *surf) {
  draw_rect(surf, this->position, this->bounds, 0xFFFFFF);
}


/* Apply a force to an objects acceleration vetor */
void Object::apply_force(Vector2 &F) {
    this->acceleration += F;
}


/* Update all objects in the list */
void Object::update_objects(double dt) {
  for (auto obj : objects) {
    obj->update(dt);

    obj->velocity += obj->acceleration;
    obj->position += obj->velocity;
  }
}


/* Render all objects in the list */
void Object::render_objects(SDL_Surface *s) {
  for (auto obj : objects) {
    obj->render(s);
  }
}


/* Compare an object to a tag */
bool Object::operator==(const unsigned id) {
  return this->id == id;
}
