#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <memory>

#include "game_object.h"

class Building : public GameObject {
 public:
  Building(int tower_type, int id, Coordinate position);
  explicit Building(const std::shared_ptr<Building>& other);

  // Determines whether the point is inside the building;
  // Is used to check whether mouse press was on the building;
  // Default realization is for circle-shaped buildings.
  virtual bool IsInside(Coordinate point) const;
  virtual void Upgrade();

  void Tick() override;
  void Draw(QPainter* painter) const override;

  int GetId() const;
  int GetTowerType() const;
  int GetRadius() const;

 protected:
  int id_;
  const int kTowerType;
  const int kRadius_ = 15;
};

#endif  // GAMEOBJECT_BUILDING_H_
