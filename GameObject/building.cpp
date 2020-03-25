#include <QDebug>

#include "building.h"

Building::Building(int id, Coordinate pos)
    : GameObject(pos), kBuildingId_(id) {}

int Building::GetId() const {
  return kBuildingId_;
}

int Building::GetRadius() const {
  return kRadius_;
}

bool Building::IsInside(Coordinate point) const {
  return point.GetBetween(position_).GetLength() <= kRadius_;
}

void Building::Upgrade() {
  qDebug() << "building #" << kBuildingId_ << " upgraded";
}

Building::Building(int id) : Building(id, Coordinate(0, 0)) {}
