#include "Vec.h"

#include <cmath>

static double angleBetweenVectors(Vector2& A, const Vector2& B) {
    // Compute dot product and magnitudes
    double dot = A * B;
    double magA = A.mag();
    double magB = B.mag();

    // Avoid division by zero and clamp the cosine value to the range [-1, 1]
    double cosTheta = dot / (magA * magB);
    cosTheta = std::fmin(1.0, std::fmax(-1.0, cosTheta));  // Clamp to [-1, 1]

    // Return the angle in radians
    return acos(cosTheta);
}

Vector2::Vector2(void) : Vector2(0, 0) {}
Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2::Vector2(const Vector2 &rhs) {
  this->x = rhs.x;
  this->y = rhs.y;
}

void Vector2::operator=(const Vector2 &rhs) {
  this->x = rhs.x;
  this->y = rhs.y;
}

Vector2 Vector2::operator+(const Vector2 &rhs) {
  return Vector2(this->x + rhs.x, this->y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2 &rhs) {
  return Vector2(this->x - rhs.x, this->y - rhs.y);
}

Vector2 Vector2::operator*(const double scaler) {
  return Vector2(this->x * scaler, this->y * scaler);
}

Vector2 Vector2::operator/(const double scaler) {
  return Vector2(this->x / scaler, this->y / scaler);
}

void Vector2::operator+=(const Vector2 &rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
}

void Vector2::operator*=(const double scaler) {
  this->x *= scaler;
  this->y *= scaler;
}

void Vector2::operator/=(const double scaler) {
  this->x /= scaler;
  this->y /= scaler;
}

double Vector2::operator*(const Vector2 &rhs) { // dot product
  return (this->x * rhs.x) + (this->y * rhs.y);
}

double Vector2::cross_prod(const Vector2 &rhs) { // TODO: Fix;
  return this->mag() * rhs.mag() * sin(angleBetweenVectors(*this, rhs)); // |A||B|*sin(theta)
}

double Vector2::mag() const {
  return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

std::ostream &operator<<(std::ostream &out, const Vector2 &vec) {
  out << "< x: " << vec.x << " y: " << vec.y << " >";

  return out;
}
