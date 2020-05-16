#include "auric_field.h"

AuricField::AuricField(double effect_radius, int effect_id)
    : effect_radius_(effect_radius), effect_id_(effect_id) {}

void AuricField::Draw(QPainter* painter, const SizeHandler& size_handler,
                      Coordinate position) const {
  if (!IsValid() && position == Coordinate(-1000, -1000)) {
    return;
  }
  painter->save();

  if (position == Coordinate(-1000, -1000)) {
    position = *carrier_coordinate_;
  }

  painter->setPen(Qt::transparent);
  Coordinate point = size_handler.GameToWindowCoordinate(position);
  Size size = size_handler.GameToWindowSize(
      Size(effect_radius_, effect_radius_));

  Coordinate gradient_center =
      size_handler.GameToWindowCoordinate(position);

  QRadialGradient gradient(gradient_center.x,
                           gradient_center.y * 1
                               / constants::kSemiMinorCoefficient,
                           size.width);

  QColor color(Qt::blue);
  color.setAlpha(60);
  gradient.setColorAt(0, Qt::transparent);
  gradient.setColorAt(0.80, Qt::transparent);
  gradient.setColorAt(1, color);
  painter->setBrush(gradient);
  painter->scale(1, constants::kSemiMinorCoefficient);

  painter->drawEllipse(QPointF(point.x,
                               point.y * 1 / constants::kSemiMinorCoefficient),
                       size.width,
                       size.height);
  painter->restore();
}

void AuricField::SetCarrierCoordinate(Coordinate* carrier_coordinates) {
  carrier_coordinate_ = carrier_coordinates;
}

int AuricField::GetEffectId() const {
  return effect_id_;
}

bool AuricField::IsInRadius(const Coordinate& coordinate) const {
  return coordinate.IsInEllipse(*carrier_coordinate_,
                                effect_radius_);
}

bool AuricField::IsValid() const {
  return effect_id_ != -1;
}
