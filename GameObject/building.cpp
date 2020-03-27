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

Building::Building(int tower_type, int id, Coordinate position) :
    GameObject(position), id_(id), kTowerType(tower_type) {}

int Building::GetTowerType() const {
  return kTowerType;
}

Building::Building(std::shared_ptr<Building> other) :
  Building(other->kTowerType, other->id_, other->position_) {}

void Building::Tick() {}

void Building::Draw(QPainter* painter) const {
  painter->save();

  painter->setBrush(Qt::gray);
  painter->drawEllipse(QPoint(position_.x, position_.y), kRadius_, kRadius_);

  painter->restore();
}
