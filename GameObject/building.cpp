#include <QDebug>

#include "building.h"

int Building::GetId() const {
  return id_;
}

int Building::GetInteractionRadius() const {
  return kInteractionRadius;
}

bool Building::IsInside(Coordinate point) const {
  return point.GetBetween(position_).GetLength() <= kInteractionRadius;
}

void Building::Upgrade() {
  current_level_++;
  qDebug() << "building #" << id_ << " upgraded to" << current_level_;
}

void Building::SetParameters(int id, const QColor& draw_color, int max_level,
    int action_range) {
  id_ = id;
  draw_color_ = draw_color;
  max_level_ = max_level;
  current_level_ = 1;
  action_range_ = action_range;
}

Building::Building(const Building& other) {
  SetParameters(other.id_, other.draw_color_, other.max_level_,
      other.action_range_);
  current_level_ = other.current_level_;
}

void Building::Draw(QPainter* painter) const {
  painter->save();
  painter->setBrush(draw_color_);
  painter->drawEllipse(QPoint(position_.x, position_.y),
                       kInteractionRadius,
                       kInteractionRadius);

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
