#ifndef VIEW_TOWER_MENU_H_
#define VIEW_TOWER_MENU_H_

#include <memory>
#include <vector>
#include <algorithm>

#include <QPainter>
#include <GameObject/building.h>

#include "Model/coordinate.h"
#include "tower_menu_option.h"

class TowerMenu {
 public:
  // Note: options are expected to be not empty
  TowerMenu(int creation_time, const std::shared_ptr<Building>& tower,
            const std::vector<std::shared_ptr<TowerMenuOption>>& options);

  std::shared_ptr<Building> GetTower() const;
  // Returns nullptr if none was pressed
  std::shared_ptr<TowerMenuOption> GetPressedOption(Coordinate position);
  void Hover(const std::shared_ptr<TowerMenuOption> option);
  void Unhover();

  void Draw(QPainter* painter, int current_time);

 private:
  int creation_time_;

  std::shared_ptr<Building> tower_;
  std::vector<std::shared_ptr<TowerMenuOption>> options_;
  std::shared_ptr<TowerMenuOption> hovered_;

  // Won't be needed if we change buttons so that they circle around the tower
  int container_length_;

  const int kAnimationDuration = 100;

  // Calculates the position of ith button at current time
  Coordinate GetCoordinate(int i, int time);
};

#endif  // VIEW_TOWER_MENU_H_
