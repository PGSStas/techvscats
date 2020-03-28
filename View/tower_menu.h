#ifndef VIEW_TOWER_MENU_H_
#define VIEW_TOWER_MENU_H_

#include <memory>
#include <vector>

#include <QPainter>

#include "Model/coordinate.h"
#include "tower_menu_option.h"

class TowerMenu {
 public:
  // Note: options are expected to be not empty
  TowerMenu(Coordinate tower_position,
            int tower_radius,
            const std::vector<std::shared_ptr<TowerMenuOption>>& options);

  Coordinate GetTowerPosition() const;
  int GetTowerRadius() const;
  // Returns nullptr if none was pressed
  std::shared_ptr<TowerMenuOption> GetPressedOption(Coordinate position);

  void Draw(QPainter* painter);

 private:
  Coordinate tower_position_;
  int tower_radius_;
  std::vector<std::shared_ptr<TowerMenuOption>> options_;

  // Won't be needed if we change buttons so that they circle around the tower
  int container_length_;

  // Calculates the position of ith button
  Coordinate GetCoordinateByIndex(int i);
};

#endif  // VIEW_TOWER_MENU_H_
