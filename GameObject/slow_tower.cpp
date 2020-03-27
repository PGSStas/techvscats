  #include "slow_tower.h"

void SlowTower::Draw(QPainter* painter) const {
  painter->save();

  painter->setBrush(Qt::red);
  painter->drawEllipse(QPoint(position_.x, position_.y), kRadius_, kRadius_);

  painter->restore();
}

SlowTower::SlowTower(int id, Coordinate position) :
  ActiveTower(2, id, position) {}

SlowTower::SlowTower(std::shared_ptr<Building> other) : ActiveTower(other) {}