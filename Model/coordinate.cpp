#include "coordinate.h"

Coordinate::Coordinate(double x, double y)
    : x(x), y(y) {}

bool Coordinate::operator==(Coordinate right) const {
  return (std::abs(x - right.x) < kEpsilon)
      && (std::abs(y - right.y) < kEpsilon);
}

Coordinate& Coordinate::operator*=(double right) {
  x *= right;
  y *= right;
  return *this;
}

Coordinate& Coordinate::operator/=(double right) {
  x /= right;
  y /= right;
  return *this;
}

Coordinate Coordinate::operator*(double right) const {
  return Coordinate(x * right, y * right);
}

Coordinate Coordinate::operator/(double right) const {
  return Coordinate(x / right, y / right);
}

Size Coordinate::GetVectorTo(Coordinate right) const {
  return Size(right.x - x, right.y - y);
}

Coordinate Coordinate::operator+(Size right) const {
  return Coordinate(x + right.width, y + right.height);
}

Coordinate Coordinate::operator-(Size right) const {
  return Coordinate(x - right.width, y - right.height);
}

Coordinate& Coordinate::operator+=(Size right) {
  *this = *this + right;
  return *this;
}

Coordinate& Coordinate::operator-=(Size right) {
  *this = *this - right;
  return *this;
}

void Coordinate::MoveTo(Coordinate destination, double vector_length) {
  Size move_direction = GetVectorTo(destination);

  if (std::abs(move_direction.GetLength()) > kEpsilon) {
    move_direction /= move_direction.GetLength();
    move_direction *= vector_length;
  }
  if ((*this + move_direction).GetVectorTo(destination).width
      * GetVectorTo(destination).width <= 0) {
    *this = destination;
  } else {
    *this += move_direction;
  }
}
