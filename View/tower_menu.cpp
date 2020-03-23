#include "tower_menu.h"

void TowerMenu::Draw(QPainter* p) {
  p->save();

  int length =
      options_[0]->GetSize() * options_.size() + 10 * (options_.size() - 1);
  for (size_t i = 0; i < options_.size(); i++) {
    int x = tower_pos_.x - length / 2 + i * options_[i]->GetSize() + i * 10;
    int y = tower_pos_.y + tower_radius_ + 5;
    options_[i]->Draw(p, Coordinate(x, y));
  }

  p->restore();
}

TowerMenu::TowerMenu(Coordinate tower_pos, int tower_radius,
    const std::vector<std::shared_ptr<TowerMenuOption>>& options) :
    tower_pos_(tower_pos),
    tower_radius_(tower_radius),
    options_(options) {}

int TowerMenu::GetTowerRadius() const {
  return tower_radius_;
}

Coordinate TowerMenu::GetTowerPos() const {
  return tower_pos_;
}
