#include "size.h"

Size::Size(double x, double y) noexcept: width(x), height(y) {}

double Size::GetLength() const {
  return std::hypot(width, height);
}

Size& Size::Normalize() {
  *this /= GetLength();
  return *this;
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
  return (width - right.width < constants::kEpsilon)
      && (height - right.height < constants::kEpsilon);
}
bool Size::operator!=(Size right) const {
  return !(*this == right);
}
