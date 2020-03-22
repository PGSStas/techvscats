#include "coordinate.h"

Coordinate Coordinate::operator+(const Coordinate& right) {
  return Coordinate({x + right.x, y + right.y});
}

Coordinate Coordinate::operator-(const Coordinate& right) {
  return Coordinate({x - right.x, y - right.y});
}

Coordinate& Coordinate::operator+=(const Coordinate& right) {
  x += right.x;
  y += right.y;
  return *this;
}

bool Coordinate::operator==(const Coordinate& right) {
  return x == right.x && y == right.y;
}

double Coordinate::Lentgth() {
  return std::sqrt(x * x + y * y);
}

Coordinate& Coordinate::operator*=(double right) {
  x *= right;
  y *= right;
  return *this;
}

Coordinate& Coordinate::operator/=(const double right) {
  x /= right;
  y /= right;
  return *this;
}
Coordinate Coordinate::VectorTo(const Coordinate& right) {
  Coordinate tmp = *this;
  tmp.x = right.x - tmp.x;
  tmp.y = right.y - tmp.y;
  return tmp;
}
