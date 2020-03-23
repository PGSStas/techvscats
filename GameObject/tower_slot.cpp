#include "tower_slot.h"

void TowerSlot::Draw(QPainter* p, Coordinate pos) const {
  p->save();

  p->setBrush(Qt::gray);
  p->drawEllipse(QPoint(pos.x, pos.y), kRadius_, kRadius_);

  p->restore();
}

void TowerSlot::Tick() {}

TowerSlot::TowerSlot(Coordinate pos) : Building(0, pos) {}
