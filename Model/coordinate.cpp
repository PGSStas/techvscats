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

Size Coordinate::GetDistanceTo(Coordinate right) {
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

void Coordinate::MoveTo(Coordinate destination, double speed) {
  Size move_direction = GetDistanceTo(destination);

  if (std::abs(move_direction.GetLength()) > kEpsilon) {
    move_direction /= move_direction.GetLength();
    move_direction *= speed;
  }
  if ((*this + move_direction).GetDistanceTo(destination).width
      * GetDistanceTo(destination).width <= 0) {
    *this = destination;
  } else {
    *this += move_direction;
  }
}
