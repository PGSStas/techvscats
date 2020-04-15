#ifndef VIEW_TOWER_MENU_H_
#define VIEW_TOWER_MENU_H_

#include <algorithm>
#include <memory>
#include <vector>

#include <QPainter>

#include "GameObject/building.h"
#include "Model/coordinate.h"
#include "tower_menu_option.h"

class TowerMenu {
 public:
  // Note: options are expected to be not empty
  TowerMenu(int creation_time, const Building& tower,
            std::vector<std::shared_ptr<TowerMenuOption>> options);

  void Hover(const std::shared_ptr<TowerMenuOption>& option);
  void Draw(QPainter* painter, const SizeHandler& size_handler,
            int current_time) const;

  std::shared_ptr<TowerMenuOption> GetButtonInside(Coordinate position) const;
  const Building& GetTower() const;

 private:
  std::shared_ptr<TowerMenuOption> hovered_option_;
  std::vector<std::shared_ptr<TowerMenuOption>> options_;
  const Building& tower_;
  uint container_length_;
  int creation_time_;

  const int kAnimationDuration = 100;
  const int kIndentBetweenButtons = 10;
  const int kIndentFromTower = 5;

 private:
  Coordinate CalculateCoordinate(int i, int size) const;
};

#endif  // VIEW_TOWER_MENU_H_
