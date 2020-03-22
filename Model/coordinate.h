#ifndef MODEL_COORDINATE_H_
#define MODEL_COORDINATE_H_

#include <cmath>

class Coordinate {
 public:
  Coordinate() = default;
  Coordinate(double position_x, double position_y);

  double x;
  double y;

  double Lentgth();
  Coordinate VectorTo(const Coordinate& right);

  Coordinate operator+(const Coordinate& right);
  Coordinate operator-(const Coordinate& right);
  Coordinate& operator+=(const Coordinate& right);
  Coordinate& operator*=(double right);
  Coordinate& operator/=(double right);
  bool operator==(const Coordinate& right);
};

#endif  // MODEL_COORDINATE_H_
