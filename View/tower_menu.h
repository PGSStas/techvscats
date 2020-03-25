#ifndef VIEW_TOWER_MENU_H
#define VIEW_TOWER_MENU_H

#include <memory>

#include <QPainter>

#include "Model/coordinate.h"
#include "tower_menu_option.h"

class TowerMenu {
 public:
  // Note: options are expected to be not empty
  TowerMenu(Coordinate tower_pos,
            int tower_radius,
            const std::vector<std::shared_ptr<TowerMenuOption>>& options);

  Coordinate GetTowerPos() const;
  int GetTowerRadius() const;
  // Returns nullptr if none was pressed
  std::shared_ptr<TowerMenuOption> GetPressedOption(Coordinate pos);

  void Draw(QPainter* p);

 private:
  Coordinate tower_pos_;
  int tower_radius_;
  std::vector<std::shared_ptr<TowerMenuOption>> options_;

  // Won't be needed if we change buttons so that they circle around the tower
  int container_length_;

 private:
  // Calculates the position of ith button
  Coordinate GetCoordinateByI(int i);
};

#endif // VIEW_TOWER_MENU_H
