#include "tower_menu_option.h"

int TowerMenuOption::GetSize() const {
  return kSize_;
}

bool TowerMenuOption::IsPressed(Coordinate option_pos, Coordinate press_pos) {
  return press_pos.x >= option_pos.x && press_pos.y >= option_pos.y
      && press_pos.x <= option_pos.x + kSize_
      && press_pos.y <= option_pos.y + kSize_;
}

void TowerMenuOption::Draw(QPainter* p, Coordinate pos) {
  p->save();

  // to be drawn from picture, e. g. "menubutton_id_.png"
  p->setBrush(Qt::lightGray);
  p->drawRect(pos.x, pos.y, kSize_, kSize_);
  p->drawText(pos.x, pos.y, QString::number(id_));

  p->restore();
}

void TowerMenuOption::Action() {
  action_();
}

TowerMenuOption::TowerMenuOption(int id, const std::function<void()>& action)
    : id_(id), action_(action) {}

