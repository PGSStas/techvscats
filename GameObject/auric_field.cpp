#include "auric_field.h"

const double AuricField::kSemiMinorCoefficient = 0.9;

AuricField::AuricField(double effect_radius, int effect_id)
    : effect_radius_(effect_radius), effect_id_(effect_id) {}

void AuricField::Draw(QPainter* painter,
                      const SizeHandler& size_handler) const {
  if (!IsValid()) {
    return;
  }
  painter->save();

  painter->setPen(Qt::transparent);
  Coordinate point = size_handler.GameToWindowCoordinate(
      *carrier_coordinate_
          - Size(effect_radius_, effect_radius_ * kSemiMinorCoefficient));
  Size size = size_handler.GameToWindowSize(
      Size(effect_radius_ * 2, effect_radius_ * 2));

  Coordinate gradient_center = size_handler.GameToWindowCoordinate(
      *carrier_coordinate_);

  QRadialGradient gradient(gradient_center.x,
      gradient_center.y * 1 / kSemiMinorCoefficient, size.width / 2);

  QColor color(Qt::blue);
  color.setAlpha(60);
  gradient.setColorAt(0, Qt::transparent);
  gradient.setColorAt(0.80, Qt::transparent);
  gradient.setColorAt(1, color);
  painter->setBrush(gradient);
  painter->scale(1, 0.9);

  painter->drawEllipse(point.x, point.y * 1 / kSemiMinorCoefficient,
                       size.width, size.height);
  painter->restore();
}

void AuricField::SetCarrierCoordinate(Coordinate* carrier_coordinates) {
  carrier_coordinate_ = carrier_coordinates;
}

int AuricField::GetEffectId() const {
  return effect_id_;
}

bool AuricField::IsInRadius(const Coordinate& coordinate) const {
  // Now, our aura have shape of ellipse.
  // Our focal distance - sqrt(a^2 - b^2) of effect radius.
  double foci_coefficient =
      std::sqrt(1 - kSemiMinorCoefficient * kSemiMinorCoefficient);
  Coordinate first_foci(carrier_coordinate_->x +
      foci_coefficient * effect_radius_, carrier_coordinate_->y);
  Coordinate second_foci(carrier_coordinate_->x -
      foci_coefficient * effect_radius_, carrier_coordinate_->y);
  return coordinate.GetVectorTo(first_foci).GetLength()
      + coordinate.GetVectorTo(second_foci).GetLength()
      <= 2 * effect_radius_ + kEpsilon;
}

bool AuricField::IsValid() const {
  return effect_id_ != -1;
}
