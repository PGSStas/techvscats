#include "build_option.h"

BuildOption::BuildOption(const Building& tower_to_build_) :
  TowerMenuOption(tower_to_build_.GetId()), tower_to_build_(tower_to_build_) {
}

void BuildOption::Draw(QPainter* p, Coordinate pos) {
  p->save();

  p->setBrush(Qt::lightGray);
  p->drawRect(pos.x, pos.y, kSize_, kSize_);
  tower_to_build_.Draw(p, pos + Coordinate(kSize_/2,kSize_/2));

  p->restore();
}
