#include "tower_menu_option.h"

int TowerMenuOption::GetMaxSize() const {
  return kMaxSize_;
}

bool TowerMenuOption::IsPressed(Coordinate option_position,
    Coordinate press_position) const {
  return press_position.x >= option_position.x
      && press_position.y >= option_position.y
      && press_position.x <= option_position.x + kMaxSize_
      && press_position.y <= option_position.y + kMaxSize_;
}

void TowerMenuOption::Draw(QPainter* painter, Coordinate position,
                          Size current_size) const {
  painter->save();

  // to be drawn from picture, e. g. "menubutton_id_.png"
  painter->setBrush(Qt::lightGray);
  painter->drawRect(position.x, position.y,
      current_size.width, current_size.height);
  painter->drawText(position.x, position.y,
      QString::number(replacing_tower_.GetId()));

  painter->restore();
}

void TowerMenuOption::MakeAction() {
  action_();
}

TowerMenuOption::TowerMenuOption(
    const Building& replacing_tower,
    const std::function<void()>& action)
    : replacing_tower_(replacing_tower), action_(action) {}

const Building& TowerMenuOption::GetReplacingTower() const {
  return replacing_tower_;
}
