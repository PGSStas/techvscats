#ifndef VIEW_TOWER_MENU_OPTION_H_
#define VIEW_TOWER_MENU_OPTION_H_

#include <functional>
#include <QPainter>

#include "Model/coordinate.h"

class TowerMenuOption {
 public:
  TowerMenuOption(int id, const std::function<void()>& action);

  int GetSize() const;
  int GetId() const;
  // Determines if press_position is inside a button
  // with left top angle in option_position
  bool IsPressed(Coordinate option_position, Coordinate press_position);

  void Draw(QPainter* painter, Coordinate position);
  void Action();

 private:
  const int kSize_ = 36;
  int id_;
  std::function<void()> action_;
};

#endif  // VIEW_TOWER_MENU_OPTION_H_
