#include <QDebug>

#include "building.h"

int Building::GetId() const {
  return id_;
}

int Building::GetRadius() const {
  return kRadius_;
}

bool Building::IsInside(Coordinate point) const {
  return point.GetBetween(position_).GetLength() <= kRadius_;
}

void Building::Upgrade() {
  current_level_++;
  qDebug() << "building #" << id_ << " upgraded to" << current_level_;
}

Building::Building(const std::list<std::shared_ptr<Enemy>>& enemies,
                   int tower_type) :
    enemies_(enemies), kTowerType(tower_type) {

}

void Building::SetParameters(int id,
                             const QColor& draw_color,
                             int max_level) {
  id_ = id;
  draw_color_ = draw_color;
  max_level_ = max_level;
  current_level_ = 0;
}

int Building::GetTowerType() const {
  return kTowerType;
}

Building::Building(const std::shared_ptr<Building>& other) :
    Building(other->enemies_, other->kTowerType) {
  SetParameters(other->id_, other->draw_color_, max_level_ = other->max_level_);
}

void Building::Tick() {}

void Building::Draw(QPainter* painter) const {
  painter->save();
  painter->setBrush(draw_color_);
  painter->drawEllipse(QPoint(position_.x, position_.y), kRadius_, kRadius_);
  painter->restore();
}

int Building::GetMaxLevel() const {
  return max_level_;
}

int Building::GetCurrentLevel() const {
  return current_level_;
}
