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


