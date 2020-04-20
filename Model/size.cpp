#include "size.h"

Size::Size(double x, double y) noexcept : width(x), height(y) {}

double Size::GetLength() const {
  return std::sqrt(width * width + height * height);
}

Size Size::operator*(double right) const {
  return Size(width * right, height * right);
}

Size Size::operator/(double right) const {
  return Size(width / right, height / right);
}

Size& Size::operator*=(double right) {
  *this = *this * right;
  return *this;
}

Size& Size::operator/=(double right) {
  *this = *this / right;
  return *this;
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

Size& Size::operator-=(Size right) {
  *this = *this - right;
  return *this;
}

bool Size::operator==(Size right) const {
  return (width - right.width < kSizeEpsilon)
      && (height - right.height < kSizeEpsilon);
}
