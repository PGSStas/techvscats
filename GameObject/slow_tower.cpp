#include "slow_tower.h"

void SlowTower::Draw(QPainter* p, Coordinate pos) const {
  p->save();

  p->setBrush(Qt::red);
  p->drawEllipse(QPoint(pos.x, pos.y), kRadius_, kRadius_);

  p->restore();
}

void SlowTower::Tick() {}

SlowTower::SlowTower(Coordinate pos) : ActiveTower(2, pos) {
}
