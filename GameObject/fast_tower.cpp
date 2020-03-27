#include "fast_tower.h"

void FastTower::Draw(QPainter* painter) const {
  painter->save();

  painter->setBrush(Qt::blue);
  painter->drawEllipse(QPoint(position_.x, position_.y), kRadius_, kRadius_);

  painter->restore();
}

FastTower::FastTower(int id, Coordinate position) :
  ActiveTower(1, id, position) {}

FastTower::FastTower(std::shared_ptr<Building> other) : ActiveTower(other) {}
