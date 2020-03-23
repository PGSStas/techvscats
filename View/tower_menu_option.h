#ifndef TOWER_MENU_OPTION_H
#define TOWER_MENU_OPTION_H

#include <QPainter>
#include "Model/coordinate.h"

class TowerMenuOption {
 public:
  int GetSize() const;
  virtual void Draw(QPainter* p, Coordinate pos) = 0;

 protected:
  const int kSize_ = 36;
  const int kId_;

 protected:
  explicit TowerMenuOption(int id);
};

#endif //TOWER_MENU_OPTION_H
