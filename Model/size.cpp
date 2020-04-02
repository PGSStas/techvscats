#include "size.h"

Size::Size(double x, double y) : width_(x), height_(y) {}

double Size::GetLength() const {
  return std::sqrt(width_ * width_ + height_ * height_);
}

Size Size::operator*(double right) const {
  return Size(width_ * right, height_ * right);
}

Size Size::operator/(double right) const {
  return Size(width_ / right, height_ / right);
}

bool Size::operator==(const Size& right) const {
  return width_ == right.width_ && height_ == right.height_;
}

Size Size::operator+(const Size& right) const {
  return Size(width_ + right.width_, height_ + right.height_);
}

Size Size::operator-(const Size& right) const {
  return Size(width_ - right.width_, height_ - right.height_);
}

Size& Size::operator+=(const Size& right) {
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