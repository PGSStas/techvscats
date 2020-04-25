#include "coordinate.h"

Coordinate::Coordinate(double x, double y) noexcept
    : x(x), y(y) {}

Size Coordinate::GetVectorTo(Coordinate right) const {
  return Size(right.x - x, right.y - y);
}

bool Coordinate::IsInEllipse(Coordinate center, double ellipse_radius) const {
  // Now, our aura have shape of ellipse.
  // Our focal distance - sqrt(a^2 - b^2) of effect radius.
  double foci_coefficient = std::sqrt(
      1 - constants::kSemiMinorCoefficient * constants::kSemiMinorCoefficient);
  Coordinate first_foci(center.x + foci_coefficient * ellipse_radius,
                        center.y);
  Coordinate second_foci(center.x - foci_coefficient * ellipse_radius,
                         center.y);
  return GetVectorTo(first_foci).GetLength() +
      GetVectorTo(second_foci).GetLength()
      <= 2 * ellipse_radius + constants::kEpsilon;
}

Coordinate Coordinate::operator*(double right) const {
  return Coordinate(x * right, y * right);
}

Coordinate Coordinate::operator/(double right) const {
  return Coordinate(x / right, y / right);
}

Coordinate& Coordinate::operator*=(double right) {
  x *= right;
  y *= right;
  return *this;
}

Coordinate& Coordinate::operator/=(double right) {
  x /= right;
  y /= right;
  return *this;
}

Coordinate& Coordinate::operator+=(Size right) {
  *this = *this + right;
  return *this;
}

Coordinate Coordinate::operator+(Size right) const {
  return Coordinate(x + right.width, y + right.height);
}

Coordinate& Coordinate::operator-=(Size right) {
  *this = *this - right;
  return *this;
}

Coordinate Coordinate::operator-(Size right) const {
  return Coordinate(x - right.width, y - right.height);
}

bool Coordinate::operator==(Coordinate right) const {
  return (std::abs(x - right.x) < constants::kEpsilon)
      && (std::abs(y - right.y) < constants::kEpsilon);
}
