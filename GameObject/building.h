#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <memory>

#include "game_object.h"

class Building : public GameObject {
 public:
  explicit Building(int tower_type = 0);
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
  int GetMaxLevel() const;
  int GetCurrentLevel() const;

  void SetParameters(int id, const QColor& draw_color, int max_level);
 protected:
  int id_;
  // later her should be imgs to draw
  QColor draw_color_;
  int max_level_;
  int current_level_;
  const int kTowerType;
  const int kRadius_ = 15;
};

#endif  // GAMEOBJECT_BUILDING_H_
