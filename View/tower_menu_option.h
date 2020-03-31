#ifndef VIEW_TOWER_MENU_OPTION_H_
#define VIEW_TOWER_MENU_OPTION_H_

#include <functional>
#include <memory>

#include <QPainter>

#include "GameObject/building.h"
#include "Model/coordinate.h"

class TowerMenuOption {
 public:
  TowerMenuOption(const std::shared_ptr<const Building>& replacing_tower,
      const std::function<void()>& action);

  int GetMaxSize() const;
  std::shared_ptr<const Building> GetReplacingTower() const;
  // Determines if press_position is inside a button
  // with left top angle in option_position
  bool IsPressed(Coordinate option_position, Coordinate press_position);

  void Draw(QPainter* painter, Coordinate position, int current_size);
  void Action();

 private:
  const int kMaxSize_ = 36;
  std::shared_ptr<const Building> replacing_tower_;
  std::function<void()> action_;
};

#endif  // VIEW_TOWER_MENU_OPTION_H_
