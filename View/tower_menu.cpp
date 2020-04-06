#include "tower_menu.h"

TowerMenu::TowerMenu(int creation_time,
    const std::shared_ptr<const Building>& tower,
    const std::vector<std::shared_ptr<TowerMenuOption>>& options) :
    creation_time_(creation_time),
    tower_(tower),
    options_(options) {
  container_length_ =
      options_[0]->GetMaxSize() * options_.size() + 10 * (options_.size() - 1);
}

void TowerMenu::Draw(QPainter* painter, int current_time) const {
  painter->save();

  painter->setBrush(QColor(148, 148, 148, 0.33 * 255));
  if (hovered_option_ == nullptr) {
    painter->drawEllipse(QPoint(tower_->GetPosition().x,
                                tower_->GetPosition().y),
                         tower_->GetAttackRange(), tower_->GetAttackRange());
  } else {
    painter->drawEllipse(QPoint(tower_->GetPosition().x,
            tower_->GetPosition().y),
                         hovered_option_->GetReplacingTower().GetAttackRange(),
                         hovered_option_->GetReplacingTower().GetAttackRange());
  }

  int time_delta = std::min(current_time - creation_time_, kAnimationDuration);
  int button_size = (time_delta * 1.0 / kAnimationDuration) *
                    options_[0]->GetMaxSize();
  for (size_t i = 0; i < options_.size(); i++) {
    options_[i]->Draw(painter,
        GetCoordinate(i, button_size), button_size);
  }

  painter->restore();
}

std::shared_ptr<const Building> TowerMenu::GetTower() const {
  return tower_;
}

std::shared_ptr<TowerMenuOption>
    TowerMenu::GetButtonContaining(Coordinate position) const {
  for (size_t i = 0; i < options_.size(); i++) {
    if (options_[i]->IsPressed(GetCoordinate(i, options_[i]->GetMaxSize()),
        position)) {
      return options_[i];
    }
  }
  return nullptr;
}

Coordinate TowerMenu::GetCoordinate(int i, int size) const {
  int x = tower_->GetPosition().x -
      container_length_ / 2 + i * options_[i]->GetMaxSize() + i * 10
      + (options_[i]->GetMaxSize() - size) / 2;
 // int y = tower_->GetPosition().y + tower_->GetInteractionRadius() + 5
  int y = tower_->GetPosition().y + 10 + 5
          + (options_[i]->GetMaxSize() - size) / 2;
  return Coordinate(x, y);
}

void TowerMenu::Hover(const std::shared_ptr<TowerMenuOption>& option) {
  hovered_option_ = option;
}

void TowerMenu::Unhover() {
  hovered_option_ = nullptr;
}
