#include "auric_field.h"

void AuricField::SetParameters(double effect_radius,
                               int effect_id) {
  effect_radius_ = effect_radius;
  effect_id_ = effect_id;
}

bool AuricField::IsInRadius(const Coordinate& coordinate) const {
  return carrier_coordinate_->GetVectorTo(coordinate).GetLength()
      <= effect_radius_ + kEpsilon;
}

int AuricField::GetEffectId() const {
  return effect_id_;
}

bool AuricField::IsValid() const {
  return effect_id_ != -1;
}

void AuricField::Draw(QPainter* painter,
                      std::shared_ptr<SizeHandler> size_handler) const {
  if (!IsValid()) {
    return;
  }
  painter->save();

  QColor blue = Qt::blue;
  blue.setAlpha(30);
  painter->setBrush(QBrush(blue));
  painter->setPen(QPen(Qt::darkBlue, 3));
  Coordinate point = size_handler->GameToWindowCoordinate(
      *carrier_coordinate_ - Size(effect_radius_, effect_radius_));
  Size size =
      size_handler->GameToWindowSize(Size(effect_radius_ * 2,
                                          effect_radius_ * 2));
  painter->drawEllipse(point.x, point.y, size.width, size.height - 10);

  painter->restore();
}

void AuricField::SetCarrierCoordinate(Coordinate* carrier_coordinates) {
  carrier_coordinate_ = carrier_coordinates;
}
