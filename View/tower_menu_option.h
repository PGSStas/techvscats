#ifndef VIEW_TOWER_MENU_OPTION_H_
#define VIEW_TOWER_MENU_OPTION_H_

#include <functional>
#include <memory>

#include <QPainter>

#include "GameObject/building.h"
#include "Model/coordinate.h"

class TowerMenuOption {
 public:
  TowerMenuOption(const Building& replacing_tower,
 const std::function<void()>& action);

  void MakeAction();
  void Draw(QPainter* painter, Coordinate position, Size current_size) const;

  const Building& GetReplacingTower() const;
  bool IsPressed(Coordinate option_position, Coordinate press_position) const;
  int GetMaxSize() const;

 private:
  std::function<void()> action_;
  const Building& replacing_tower_;
  const int kMaxSize_ = 36;
};

#endif  // VIEW_TOWER_MENU_OPTION_H_
