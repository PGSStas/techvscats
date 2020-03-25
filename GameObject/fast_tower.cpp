#include "fast_tower.h"

void FastTower::Draw(QPainter* p) const {
  p->save();

  p->setBrush(Qt::blue);
  p->drawEllipse(QPoint(position_.x, position_.y), kRadius_, kRadius_);

  p->restore();
}

void FastTower::Tick() {}

FastTower::FastTower(Coordinate pos) : ActiveTower(1, pos) {}
