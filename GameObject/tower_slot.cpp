#include "tower_slot.h"

void TowerSlot::Draw(QPainter* p) const {
  p->save();

  p->setBrush(Qt::gray);
  p->drawEllipse(QPoint(position_.x, position_.y), kRadius_, kRadius_);

  p->restore();
}

void TowerSlot::Tick() {}

TowerSlot::TowerSlot(Coordinate pos) : Building(0, pos) {}

TowerSlot::TowerSlot() : Building(0) {}
