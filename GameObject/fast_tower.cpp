#include "fast_tower.h"
void FastTower::Draw(QPainter* p, Coordinate pos) const {
  p->save();

  p->setBrush(Qt::blue);
  p->drawEllipse(QPoint(pos.x, pos.y), kRadius_, kRadius_);

  p->restore();
}

void FastTower::Tick() {}

FastTower::FastTower(Coordinate pos) : ActiveTower(1, pos) {
}
