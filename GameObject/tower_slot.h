#ifndef GAMEOBJECT_TOWER_SLOT_H
#define GAMEOBJECT_TOWER_SLOT_H

#include "building.h"

// Represents an empty place on which the player can build a tower
class TowerSlot : public Building {
 public:
  explicit TowerSlot(Coordinate pos);
  void Draw(QPainter* p) const override;
  void Tick() override;
};

#endif //TOWER_SLOT_H
