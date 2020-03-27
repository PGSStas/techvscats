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
  qDebug() << "building #" << id_ << " upgraded";
}

Building::Building(int tower_type) :
    kTowerType(tower_type) {

}

void Building::SetParameters(int id,const QColor& draw_color) {
  id_=id;
  draw_color_=draw_color;
}

int Building::GetTowerType() const {
  return kTowerType;
}

Building::Building(const std::shared_ptr<Building>& other) :
    Building(other->kTowerType) {
  id_ = other->id_;
  draw_color_ = other->draw_color_;
}

void Building::Tick() {}

void Building::Draw(QPainter* painter) const {
  painter->save();
  painter->setBrush(draw_color_);
  painter->drawEllipse(QPoint(position_.x, position_.y), kRadius_, kRadius_);

  painter->restore();
}
