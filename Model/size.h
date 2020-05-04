#ifndef MODEL_SIZE_H_
#define MODEL_SIZE_H_

#include <cmath>
#include "constants.h"

struct Size {
  double width;
  double height;

  Size() = default;
  Size(double x, double y) noexcept;

  double GetLength() const;
  Size& Normalize();

  Size operator*(double right) const;
  Size operator/(double right) const;
  Size& operator*=(double right);
  Size& operator/=(double right);

  Size operator+(Size right) const;
  Size operator-(Size right) const;
  Size& operator+=(Size right);
  Size& operator-=(Size right);

  bool operator==(Size right) const;
  bool operator!=(Size right) const;
};

#endif  // MODEL_SIZE_H_
