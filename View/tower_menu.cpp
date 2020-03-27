#include "tower_menu.h"

TowerMenu::TowerMenu(Coordinate tower_position, int tower_radius,
    const std::vector<std::shared_ptr<TowerMenuOption>>& options) :
    tower_position_(tower_position), tower_radius_(tower_radius),
    options_(options) {
  container_length_ =
      options_[0]->GetSize() * options_.size() + 10 * (options_.size() - 1);
}

void TowerMenu::Draw(QPainter* painter) {
  painter->save();

  for (size_t i = 0; i < options_.size(); i++) {
    options_[i]->Draw(painter, GetCoordinateByIndex(i));
  }

  painter->restore();
}

int TowerMenu::GetTowerRadius() const {
  return tower_radius_;
}

Coordinate TowerMenu::GetTowerPosition() const {
  return tower_position_;
}

std::shared_ptr<TowerMenuOption>
    TowerMenu::GetPressedOption(Coordinate position) {
  for (size_t i = 0; i < options_.size(); i++) {
    if (options_[i]->IsPressed(GetCoordinateByIndex(i), position)) {
      return options_[i];
    }
  }
  return nullptr;
}

Coordinate TowerMenu::GetCoordinateByIndex(int i) {
  int x = tower_position_.x -
      container_length_ / 2 + i * options_[i]->GetSize() + i * 10;
  int y = tower_position_.y + tower_radius_ + 5;
  return Coordinate(x, y);
}

