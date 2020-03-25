  #include "slow_tower.h"

void SlowTower::Draw(QPainter* p) const {
  p->save();

  p->setBrush(Qt::red);
  p->drawEllipse(QPoint(position_.x, position_.y), kRadius_, kRadius_);

  p->restore();
}

void SlowTower::Tick() {}

SlowTower::SlowTower(Coordinate pos) : ActiveTower(2, pos) {}
