#include "coordinate.h"

Coordinate Coordinate::operator+(const Coordinate& right) const {
  return Coordinate(x + right.x, y + right.y);
}

Coordinate Coordinate::operator-(const Coordinate& right) const {
  return Coordinate(x - right.x, y - right.y);
}

Coordinate& Coordinate::operator+=(const Coordinate& right) {
  x += right.x;
  y += right.y;
  return *this;
}

bool Coordinate::operator==(const Coordinate& right) const {
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

Coordinate Coordinate::operator+(const Size& right) const {
  return Coordinate(x + right.height_, y + right.width_);
}

Coordinate Coordinate::operator-(const Size& right) const {
  return Coordinate(x - right.height_, y - right.width_);
}

Coordinate& Coordinate::operator+=(const Size& right) {
  *this = *this + right;
  return *this;
}

Coordinate& Coordinate::operator-=(const Size& right) {
  *this = *this - right;
  return *this;
}
