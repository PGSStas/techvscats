#ifndef MODEL_COORDINATE_H_
#define MODEL_COORDINATE_H_

#include <cmath>
#include "size.h"

struct Coordinate {
  double x;
  double y;

  Coordinate() = default;
  Coordinate(double x, double y);
  void MoveTo(Coordinate destination, double vector_length);
  Size GetVectorTo(Coordinate right) const;

  Coordinate operator*(double right) const;
  Coordinate operator/(double right) const;
  Coordinate& operator*=(double right);
  Coordinate& operator/=(double right);

  Coordinate operator+(Size right) const;
  Coordinate& operator+=(Size right);
  Coordinate operator-(Size right) const;
  Coordinate& operator-=(Size right);

  bool operator==(Coordinate right) const;
};

#endif  // MODEL_COORDINATE_H_
