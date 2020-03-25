#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <memory>

#include "game_object.h"

class Building : public GameObject {
 public:
  Building(int id, Coordinate pos);
  explicit Building(int id);

  // Determines whether the point is inside the building;
  // Is used to check whether mouse press was on the building;
  // Default realization is for circle-shaped buildings.
  virtual bool IsInside(Coordinate point) const;

  virtual void Upgrade();

  // See: problem with vector id_to_building_ in Model
  // virtual Building* Copy() = 0;

  int GetId() const;
  int GetRadius() const;

 protected:
  const int kBuildingId_;
  const int kRadius_ = 15;
};

#endif  // GAMEOBJECT_BUILDING_H_
