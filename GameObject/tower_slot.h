#ifndef GAMEOBJECT_TOWER_SLOT_H
#define GAMEOBJECT_TOWER_SLOT_H

#include "building.h"
class TowerSlot : public Building {
 public:
  explicit TowerSlot(Coordinate pos);
  void Draw(QPainter* p, Coordinate pos) const override;
  void Tick() override;
 private:
  //const int kRadius_ = 15;
};

#endif //TOWER_SLOT_H
