#include "tower_menu.h"

void TowerMenu::HeTappedMe(uint button_index) {
  if (active_button_index_ == static_cast<int>( button_index)) {
    want_to_replace_ = true;
    Disable(false);
    return;
  }
  if (active_button_index_ != -1) {
    buttons_[active_button_index_]->EnableSecondIcon(false);
  }
  active_button_index_ = button_index;
  buttons_[active_button_index_]->EnableSecondIcon(true);

  qDebug() << "ok...";
}

TowerMenu::TowerMenu(QMainWindow* window) {
  std::vector<ButtonImagePath> button_images;
  button_images.emplace_back(
      ":resources/buttons_resources/sell_up.png",
      ":resources/buttons_resources/sell_down.png");
  button_images.emplace_back(
      ":resources/buttons_resources/building_up.png",
      ":resources/buttons_resources/building_down.png");
  button_images.emplace_back(
      ":resources/buttons_resources/building_up.png",
      ":resources/buttons_resources/building_down.png");
  button_images.emplace_back(
      ":resources/buttons_resources/building_up.png",
      ":resources/buttons_resources/building_down.png");
  ButtonImagePath confirm(
      ":resources/buttons_resources/confirm_up.png",
      ":resources/buttons_resources/confirm_down.png");

  for (auto& button_image : button_images) {
    buttons_.push_back(
        new MenuButton(Size(kSizeOfButton), window,
                       button_image.main_path, button_image.active_path));
    buttons_.back()->SetSecondIconPath(
        confirm.main_path, confirm.active_path);
    buttons_.back()->hide();
    int tap = buttons_.size() - 1;
    auto settings_button_click = [this, tap]() {
      HeTappedMe(tap);
    };
    QObject::connect(buttons_.back(), &QPushButton::clicked,
                     settings_button_click);
  }
}

void TowerMenu::Recreate(Coordinate position, int carrier_building_index,
                         const std::vector<int>& possible_buildings_id,
                         int carrier_id, const SizeHandler& size_handler) {
  for (auto& id : possible_buildings_id_) {
    buttons_[id]->EnableSecondIcon(false);
    buttons_[id]->hide();
  }
  possible_buildings_id_ = possible_buildings_id;
  for (auto& id : possible_buildings_id_) {
    buttons_[id]->SetGeometry(position - kSizeOfButton / 2, size_handler);
    buttons_[id]->show();
  }
  carrier_id_ = carrier_id;
  carrier_building_index_ = carrier_building_index;
  position_ = position;
  current_force_ = kThrowForce;
  active_button_index_ = -1;
  slow_disable = false;
  want_to_replace_ = false;
}

void TowerMenu::Tick(const SizeHandler& size_handler, int delta_time) {
  info_field_.SetPosition(position_, button_constants::kShortButtonSize,
                          button_constants::kShift);
  if (active_button_index_ != -1) {
    info_field_.Show();
  }
  if (current_force_ < 1 || possible_buildings_id_.empty()) {
    return;
  }
  info_field_.Hide();
  if (slow_disable) {
    delta_time *= -1;
  }
  int buttons_count = possible_buildings_id_.size();
  double delta_degree;
  if (info_field_.IsOnBottom()) {
    delta_degree = 180.0 / (buttons_count + 1);
  } else {
    delta_degree = -180.0 / (buttons_count + 1);
  }

  double move_degree = -90 + delta_degree;
  Size move_vector;
  current_force_ *= kSlowCoefficient;
  for (auto& id : possible_buildings_id_) {
    double radian = move_degree * std::acos(-1) / 180;
    move_degree += delta_degree;
    move_vector = Size(sin(radian), -cos(radian));
    move_vector *= current_force_ * delta_time / constants::kTimeScale;
    if (slow_disable) {
      auto first_vector =
          (buttons_[id]->GetPosition() + move_vector).GetVectorTo(
              position_ - kSizeOfButton / 2);
      auto second_vector = buttons_[id]->GetPosition().GetVectorTo(
          position_ - kSizeOfButton / 2);
      if (first_vector.GetLength() > second_vector.GetLength()
          || current_force_ < 1) {
        Disable(true);
        return;
      }
    }
    buttons_[id]->SetGeometry(
        buttons_[id]->GetPosition() += move_vector, size_handler);
  }
}

void TowerMenu::RescaleButtons(const SizeHandler& size_handler) {
  for (auto& button : buttons_) {
    button->SetGeometry(button->GetPosition(), size_handler);
  }
}

void TowerMenu::SetIsWantToReplaceToFalse() {
  want_to_replace_ = false;
}

void TowerMenu::DrawAdditionalInfo(QPainter* painter,
                                   const SizeHandler& size_handler,
                                   const Building& instance) {
  painter->save();
  info_field_.Draw(painter, size_handler);
  info_field_.SetInfo(instance);
  painter->restore();
}

void TowerMenu::Disable(bool is_fast_disable) {
  if (!is_fast_disable) {
    slow_disable = true;
    current_force_ = kThrowForce;
    return;
  }
  slow_disable = false;
  for (auto& id : possible_buildings_id_) {
    buttons_[id]->EnableSecondIcon(false);
    buttons_[id]->hide();
  }
  possible_buildings_id_.clear();
}

int TowerMenu::GetCarrierIndex() const {
  return carrier_building_index_;
}

int TowerMenu::GetSellectedTowerId() const {
  if (active_button_index_ == -1) {
    return carrier_id_;
  }
  return active_button_index_;
}

bool TowerMenu::IsEnable() const {
  return !possible_buildings_id_.empty();
}
bool TowerMenu::IsWantToReplace() const {
  return want_to_replace_;
}

