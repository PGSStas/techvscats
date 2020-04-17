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
  TowerMenu(int creation_time, const std::shared_ptr<const Building>& tower,
            const std::vector<std::shared_ptr<TowerMenuOption>>& options);

  std::shared_ptr<const Building> GetTower() const;
  // Returns the button for which position is inside or
  // nullptr if there is no such button
  std::shared_ptr<TowerMenuOption>
  GetButtonContaining(Coordinate position) const;
  void Hover(const std::shared_ptr<TowerMenuOption>& option);
  void Unhover();

  void Draw(QPainter* painter, const std::shared_ptr<SizeHandler>& size_handler,
            int current_time) const;

 private:
  int creation_time_;

  std::shared_ptr<const Building> tower_;
  std::vector<std::shared_ptr<TowerMenuOption>> options_;
  std::shared_ptr<TowerMenuOption> hovered_option_;

  // Won't be needed if we change buttons so that they circle around the tower
  int container_length_;

  const int kAnimationDuration = 100;
  const int kIndentBetweenButtons = 10;
  const int kIndentFromTower = 5;

  // Calculates the position of ith button assuming that it has given size
  Coordinate GetCoordinate(int i, int size) const;
};

#endif  // VIEW_TOWER_MENU_H_