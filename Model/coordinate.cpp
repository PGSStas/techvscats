#include "coordinate.h"

Coordinate Coordinate::operator+(const Coordinate& right) const {
  return Coordinate({x + right.x, y + right.y});
}

Coordinate Coordinate::operator-(const Coordinate& right) const {
  return Coordinate({x - right.x, y - right.y});
}

Coordinate& Coordinate::operator+=(const Coordinate& right) {
  x += right.x;
  y += right.y;
  return *this;
}

bool Coordinate::operator==(const Coordinate& right) const {
  return x == right.x && y == right.y;
}

double Coordinate::GetLength() const {
  return std::sqrt(x * x + y * y);
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

Coordinate Coordinate::GetBetween(const Coordinate& right) {
  Coordinate tmp = *this;
  tmp.x = right.x - tmp.x;
  tmp.y = right.y - tmp.y;
  return tmp;
}

Coordinate::Coordinate(double position_x, double position_y)
    : x(position_x), y(position_y) {}

Coordinate Coordinate::operator*(double right) const {
  return Coordinate({x * right, y * right});
}
Coordinate Coordinate::operator/(double right) const {
  return Coordinate({x / right, y / right});
}
