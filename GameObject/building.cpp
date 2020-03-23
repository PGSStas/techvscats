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
  return point.VectorTo(position_).GetLength() <= kRadius_;
}

void Building::Draw(QPainter* p) const {
  Draw(p, position_);
}
