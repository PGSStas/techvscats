#ifndef MODEL_SIZE_H_
#define MODEL_SIZE_H_

#include <cmath>

struct Size {
  double width_;
  double height_;

  Size() = default;
  Size(double x, double y);

  double GetLength() const;

  Size operator*(double right) const;
  Size operator/(double right) const;
  Size& operator*=(double right);
  Size& operator/=(double right);

  Size operator+(Size right) const;
  Size operator-(Size right) const;
  Size& operator+=(Size right);
  Size& operator-=(Size right);

  bool operator==(Size right) const;
};

#endif  // MODEL_SIZE_H_
