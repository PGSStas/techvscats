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

Size Coordinate::GetDistanceTo(Coordinate right) const {
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
