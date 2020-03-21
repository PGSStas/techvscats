#include "coordinate.h"

Coordinate operator+(const Coordinate& left, const Coordinate& right) {
  return Coordinate({left.x + right.x, left.y + right.y});
}

Coordinate operator-(const Coordinate& left, const Coordinate& right) {
  return Coordinate({left.x - right.x, left.y - right.y});
}

Coordinate& operator+=(Coordinate& left, const Coordinate& right) {
  left.x += right.x;
  left.y += right.y;
  return left;
}

bool operator==(const Coordinate& left, const Coordinate& right) {
  return left.x == right.x && left.y == right.y;
}


