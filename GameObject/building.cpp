#include <QDebug>

#include "building.h"

Building::Building() : GameObject(Coordinate(0, 0), Size(30, 30)) {}

int Building::GetId() const {
  return id_;
}

bool Building::IsInside(Coordinate point) const {
  return point.GetVectorTo(position_).GetLength() <= size_.width / 2;
}

void Building::Upgrade() {
  current_level_++;
  qDebug() << "building #" << id_ << " upgraded to" << current_level_;
}

void Building::SetParameters(int id,
                             const QColor& draw_color,
                             int max_level,
                             int action_range,
                             AuricField auric_field) {
  id_ = id;
  draw_color_ = draw_color;
  max_level_ = max_level;
  current_level_ = 1;
  action_range_ = action_range;
  auric_field_ = auric_field;
  auric_field_.SetCarrierCoordinate(&position_);
}

Building::Building(const Building& other) : GameObject(other) {
  SetParameters(other.id_, other.draw_color_, other.max_level_,
                other.action_range_, other.auric_field_);
  position_ = other.position_;
  size_ = other.size_;
  current_level_ = other.current_level_;
  auric_field_.SetCarrierCoordinate(&position_);
}

void Building::Draw(QPainter* painter,
                    const std::shared_ptr<SizeHandler>& size_handler) const {
  painter->save();
  painter->setBrush(draw_color_);
  Coordinate center = size_handler->GameToWindowCoordinate(position_);
  Size window_size = size_handler->GameToWindowSize(size_);
  painter->drawEllipse(QPointF(center.x, center.y),
                       window_size.width / 2,
                       window_size.height / 2);

  painter->restore();
}

void Building::Tick() {}

int Building::GetMaxLevel() const {
  return max_level_;
}

int Building::GetCurrentLevel() const {
  return current_level_;
}

int Building::GetActionRange() const {
  return action_range_;
}

const AuricField& Building::GetAuricField() const {
  return auric_field_;
}

Effect* Building::GetAppliedEffect() {
  return &applied_effect_;
}

