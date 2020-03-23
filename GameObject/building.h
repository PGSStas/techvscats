#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include "game_object.h"

class Building : public GameObject {
 public:
  Building(int id, Coordinate pos);

  // Determines whether the point is inside the building
  // Is used to check whether mouse press was on the building
  virtual bool IsInside(Coordinate point) const;

  virtual void Draw(QPainter* p, Coordinate pos) const = 0;
  void Draw(QPainter* p) const override;

  int GetId() const;
  int GetRadius() const;

 protected:
  const int kBuildingId_;
  const int kRadius_ = 15;
};

#endif  // GAMEOBJECT_BUILDING_H_
