#ifndef TOWER_MENU_OPTION_H
#define TOWER_MENU_OPTION_H

#include <QPainter>
#include <functional>
#include "Model/coordinate.h"

class TowerMenuOption {
 public:
  TowerMenuOption(int id, const std::function<void()>& action);

  int GetSize() const;
  bool IsPressed(Coordinate option_pos, Coordinate press_pos);

  void Draw(QPainter* p, Coordinate pos);
  void Action();

 private:
  const int kSize_ = 36;
  int id_;
  std::function<void()> action_;

};

#endif //TOWER_MENU_OPTION_H
