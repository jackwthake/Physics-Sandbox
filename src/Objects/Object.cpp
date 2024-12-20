#include "Object.h"

#include <list>
#include <SDL2/SDL.h>

#include "../Util/Helpers.h"

static std::list<Object *> objects;
static unsigned int _id = 0;

/* Default Constructor */
Object::Object(void) {
  this->position = { 0, 0 };
  this->bounds = { 0, 0 };

  this->velocity = Vector2();
  this->acceleration = Vector2();
  this->mass = 0.0;

  this->grounded = false;
  this->color = { 0, 0, 0 };
  this->id = _id++;

  objects.push_back(this);
}


/* Main constructor */
Object::Object(Vector2 &position, Vector2 &bounds, double mass, SDL_Color col) {
  this->position = position;
  this->bounds = bounds;

  this->velocity = Vector2();
  this->acceleration = Vector2();
  this->mass = mass;

  this->grounded = false;
  this->color = col;
  this->id = _id++;

  objects.push_back(this);
}


/* Copy constructor */
Object::Object(const Object &copy) {
this->position = copy.position;
  this->bounds = copy.bounds;

  this->velocity = copy.velocity;
  this->acceleration = copy.acceleration;
  this->mass = copy.mass;

  this->grounded = false;
  this->color = copy.color;
  this->id = copy.id; // NOTE: should it get the same id? or should a new one be used...
}


/* Render an individual object */
void Object::render(SDL_Surface *surf) {
  draw_rect(surf, this->position, this->bounds, this->color);
}


/* Apply a force to an objects acceleration vetor */
void Object::apply_force(Vector2 &F) {
    this->acceleration += F;
}


/* Update all objects in the list */
void Object::update_objects(double dt) {
  // todo apply gravity and collision check in this function
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


bool add_object(Object *obj, std::string &tag) {

}


/* Compare an object to a tag */
bool Object::operator==(const unsigned id) {
  return this->id == id;
}
