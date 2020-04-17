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

void TowerMenu::Draw(QPainter* painter,
                     const std::shared_ptr<SizeHandler>& size_handler, int current_time) const {
  painter->save();

  painter->setBrush(QColor(148, 148, 148, 0.33 * 255));
  Coordinate center =
      size_handler->GameToWindowCoordinate(tower_->GetPosition());
  if (hovered_option_ == nullptr) {
    Size radius = size_handler->GameToWindowSize(
        Size(tower_->GetActionRange(), tower_->GetActionRange()));
    painter->drawEllipse(QPointF(center.x, center.y),
                         radius.width, radius.height);
  } else {
    Size radius = size_handler->GameToWindowSize(
        Size(hovered_option_->GetReplacingTower().GetActionRange(),
             hovered_option_->GetReplacingTower().GetActionRange()));
    painter->drawEllipse(QPointF(center.x, center.y),
                         radius.width, radius.height);
  }

  int time_delta = std::min(current_time - creation_time_, kAnimationDuration);
  int button_size = (time_delta * 1.0 / kAnimationDuration) *
      options_[0]->GetMaxSize();
  Size window_button_size =
      size_handler->GameToWindowSize(Size(button_size, button_size));
  for (size_t i = 0; i < options_.size(); i++) {
    options_[i]->Draw(painter,
                      size_handler->GameToWindowCoordinate(GetCoordinate(i, button_size)),
                      window_button_size);
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
      container_length_ / 2 + i * options_[i]->GetMaxSize()
      + i * kIndentBetweenButtons + (options_[i]->GetMaxSize() - size) / 2;
  int y = tower_->GetPosition().y + tower_->GetSize().height / 2
      + kIndentFromTower + (options_[i]->GetMaxSize() - size) / 2;
  return Coordinate(x, y);
}

void TowerMenu::Hover(const std::shared_ptr<TowerMenuOption>& option) {
  hovered_option_ = option;
}

void TowerMenu::Unhover() {
  hovered_option_ = nullptr;
}
