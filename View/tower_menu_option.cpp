#include "tower_menu_option.h"

int TowerMenuOption::GetSize() const {
  return kSize_;
}

bool TowerMenuOption::IsPressed(Coordinate option_position,
    Coordinate press_position) {
  return press_position.x >= option_position.x
      && press_position.y >= option_position.y
      && press_position.x <= option_position.x + kSize_
      && press_position.y <= option_position.y + kSize_;
}

void TowerMenuOption::Draw(QPainter* painter, Coordinate position) {
  painter->save();

  // to be drawn from picture, e. g. "menubutton_id_.png"
  painter->setBrush(Qt::lightGray);
  painter->drawRect(position.x, position.y, kSize_, kSize_);
  painter->drawText(position.x, position.y, QString::number(id_));

  painter->restore();
}

void TowerMenuOption::Action() {
  action_();
}

TowerMenuOption::TowerMenuOption(int id, const std::function<void()>& action)
    : id_(id), action_(action) {}

int TowerMenuOption::GetId() const {
  return id_;
}

