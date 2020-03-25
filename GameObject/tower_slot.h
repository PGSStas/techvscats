#ifndef GAMEOBJECT_TOWER_SLOT_H_
#define GAMEOBJECT_TOWER_SLOT_H_

#include "building.h"

// Represents an empty place on which the player can build a tower
class TowerSlot : public Building {
 public:
  explicit TowerSlot(Coordinate pos);
  void Draw(QPainter* p) const override;
  void Tick() override;
};

#endif  // TOWER_SLOT_H_
