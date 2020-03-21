#ifndef MODEL_COORDINATE_H_
#define MODEL_COORDINATE_H_

struct Coordinate {
  double x;
  double y;

  friend Coordinate operator+(const Coordinate& left,
                              const Coordinate& right);
  friend Coordinate operator-(const Coordinate& left,
                              const Coordinate& right);
  friend Coordinate& operator+=(Coordinate& left, const Coordinate& right);
  friend bool operator==(const Coordinate& left, const Coordinate& right);

};

#endif  // MODEL_COORDINATE_H_
