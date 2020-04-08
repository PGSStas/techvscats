#include "size.h"

Size::Size(double x, double y) : width(x), height(y) {}

double Size::GetLength() const {
  return std::sqrt(width * width + height * height);
}

Size Size::operator*(double right) const {
  return Size(width * right, height * right);
}

Size Size::operator/(double right) const {
  return Size(width / right, height / right);
}

bool Size::operator==(Size right) const {
  return (width - right.width < kEpsilon)
      && (height - right.height < kEpsilon);
}

Size Size::operator+(Size right) const {
  return Size(width + right.width, height + right.height);
}

Size Size::operator-(Size right) const {
  return Size(width - right.width, height - right.height);
}

Size& Size::operator+=(Size right) {
  *this = *this + right;
  return *this;
}

Size& Size::operator*=(double right) {
  *this = *this * right;
  return *this;
}

Size& Size::operator/=(double right) {
  *this = *this / right;
  return *this;
}

Size& Size::operator-=(Size right) {
  *this = *this - right;
  return *this;
}
