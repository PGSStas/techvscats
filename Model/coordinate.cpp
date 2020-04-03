#include "coordinate.h"

bool Coordinate::operator==(Coordinate right) const {
  return x == right.x && y == right.y;
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

Coordinate::Coordinate(double position_x, double position_y)
    : x(position_x), y(position_y) {}

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
  return Coordinate(x + right.width_, y + right.height_);
}

Coordinate Coordinate::operator-(Size right) const {
  return Coordinate(x - right.width_, y - right.height_);
}

Coordinate& Coordinate::operator+=(Size right) {
  *this = *this + right;
  return *this;
}

Coordinate& Coordinate::operator-=(Size right) {
  *this = *this - right;
  return *this;
}
