#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <memory>

#include "game_object.h"

class Building : public GameObject {
 public:
  Building();
  Building(const Building& other);
  void SetParameters(int id, const QColor& draw_color, int max_level,
      int action_range);

  // Determines whether the point is inside the building;
  // Is used to check whether mouse press was on the building;
  // Default realization is for circle-shaped buildings.
  bool IsInside(Coordinate point) const;

  virtual void Upgrade();
  void Tick(int time) override;

  void Draw(QPainter* painter,
      const std::shared_ptr<SizeHandler>& size_handler) const override;

  int GetId() const;
  int GetMaxLevel() const;
  int GetCurrentLevel() const;
  int GetActionRange() const;

 private:
  int id_ = 0;
  int max_level_ = 0;
  int current_level_ = 0;
  int action_range_ = 75;

  const int kRadius = 45;

  // later here should be images to draw
  QColor draw_color_ = QColor("black");
};

#endif  // GAMEOBJECT_BUILDING_H_
