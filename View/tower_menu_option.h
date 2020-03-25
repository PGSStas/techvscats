#ifndef TOWER_MENU_OPTION_H
#define TOWER_MENU_OPTION_H

#include <functional>
#include <QPainter>

#include "Model/coordinate.h"

class TowerMenuOption {
 public:
  TowerMenuOption(int id, const std::function<void()>& action);

  int GetSize() const;
  int GetId() const;
  // Determines if press_pos is inside a button
  // with left top angle in option_pos
  bool IsPressed(Coordinate option_pos, Coordinate press_pos);

  void Draw(QPainter* p, Coordinate pos);
  void Action();

 private:
  const int kSize_ = 36;
  int id_;
  std::function<void()> action_;

};

#endif //TOWER_MENU_OPTION_H
