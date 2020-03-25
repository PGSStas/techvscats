#include "tower_menu.h"

TowerMenu::TowerMenu(Coordinate tower_pos, int tower_radius,
    const std::vector<std::shared_ptr<TowerMenuOption>>& options) :
    tower_pos_(tower_pos), tower_radius_(tower_radius), options_(options) {
  container_length_ =
      options_[0]->GetSize() * options_.size() + 10 * (options_.size() - 1);
}

void TowerMenu::Draw(QPainter* p) {
  p->save();

  for (size_t i = 0; i < options_.size(); i++) {
    options_[i]->Draw(p, GetCoordinateByI(i));
  }

  p->restore();
}

int TowerMenu::GetTowerRadius() const {
  return tower_radius_;
}

Coordinate TowerMenu::GetTowerPos() const {
  return tower_pos_;
}

std::shared_ptr<TowerMenuOption> TowerMenu::GetPressedOption(Coordinate pos) {
  for (size_t i = 0; i < options_.size(); i++) {
    if (options_[i]->IsPressed(GetCoordinateByI(i), pos)) {
      return options_[i];
    }
  }
  return nullptr;
}

Coordinate TowerMenu::GetCoordinateByI(int i) {
  int x = tower_pos_.x -
      container_length_ / 2 + i * options_[i]->GetSize() + i * 10;
  int y = tower_pos_.y + tower_radius_ + 5;
  return Coordinate(x, y);
}

