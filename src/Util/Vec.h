#ifndef VEC_H
#define VEC_H

#include <ostream>

class Vector2 {
public:
  Vector2(void);
  Vector2(double x, double y);
  Vector2(const Vector2 &rhs);

  void operator=(const Vector2 &rhs);

  Vector2 operator+(const Vector2 &Rhs);
  Vector2 operator-(const Vector2 &Rhs);

  Vector2 operator*(const double scaler);
  Vector2 operator/(const double scaler);

  void operator+=(const Vector2 &Rhs);

  void operator*=(const double scaler);
  void operator/=(const double scaler);

  double operator*(const Vector2 &rhs); // dot product
  double cross_prod(const Vector2 &rhs);
  double mag() const;

  friend std::ostream &operator<<(std::ostream &out, const Vector2 &);

  double x, y;
};


#endif
