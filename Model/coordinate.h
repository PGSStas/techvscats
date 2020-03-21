#ifndef MODEL_COORDINATE_H_
#define MODEL_COORDINATE_H_

struct Coordinate {
  double x;
  double y;

  Coordinate operator+(const Coordinate& right);
  Coordinate operator-(const Coordinate& right);
  Coordinate& operator+=(const Coordinate& right);
  bool operator==(const Coordinate& right);
};

#endif  // MODEL_COORDINATE_H_
