#ifndef MODEL_COORDINATE_H_
#define MODEL_COORDINATE_H_

#include <cmath>
#include "size.h"

struct Coordinate {
  double x;
  double y;

  Coordinate() = default;
  Coordinate(double position_x, double position_y);
  Size GetDistanceTo(Coordinate right);

  Coordinate operator+(const Coordinate& right) const;
  Coordinate operator-(const Coordinate& right) const;
  Coordinate operator*(double right) const;
  Coordinate operator/(double right) const;

  Coordinate& operator+=(const Coordinate& right);
  Coordinate& operator*=(double right);
  Coordinate& operator/=(double right);

  Coordinate operator+(const Size& right) const;
  Coordinate& operator+=(const Size& right);
  Coordinate operator-(const Size& right) const;
  Coordinate& operator-=(const Size& right);

  bool operator==(const Coordinate& right) const;
};

#endif  // MODEL_COORDINATE_H_
