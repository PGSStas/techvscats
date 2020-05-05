#include "tower_menu.h"

void TowerMenu::ButtonTapped(int button_index) {
  if (active_button_index_ == static_cast<int>(button_index)) {
    id_to_replace_ = true;
    Close();
    return;
  }
  if (active_button_index_ != -1) {
    buttons_[active_button_index_]->EnableSecondIcon(false);
  }
  active_button_index_ = button_index;
  buttons_[active_button_index_]->EnableSecondIcon(true);
}

TowerMenu::TowerMenu(QMainWindow* window) {
  std::vector<ButtonImagePath> button_images;
  button_images.emplace_back(
      ":resources/buttons_resources/empty_button.png",
      ":resources/buttons_resources/empty_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/default_tower_button.png",
      ":resources/buttons_resources/default_tower_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/laser_button.png",
      ":resources/buttons_resources/laser_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/bomb_button.png",
      ":resources/buttons_resources/bomb_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/support_button.png",
      ":resources/buttons_resources/support_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/upgrade_button.png",
      ":resources/buttons_resources/upgrade_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/second_upgrade_button.png",
      ":resources/buttons_resources/second_upgrade_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/upgrade_button.png",
      ":resources/buttons_resources/upgrade_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/second_upgrade_button.png",
      ":resources/buttons_resources/second_upgrade_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/upgrade_button.png",
      ":resources/buttons_resources/upgrade_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/second_upgrade_button.png",
      ":resources/buttons_resources/second_upgrade_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/upgrade_button.png",
      ":resources/buttons_resources/upgrade_button_h.png");
  button_images.emplace_back(
      ":resources/buttons_resources/second_upgrade_button.png",
      ":resources/buttons_resources/second_upgrade_button_h.png");

  ButtonImagePath confirm(
      ":resources/buttons_resources/accept.png",
      ":resources/buttons_resources/accept_h.png");

  for (auto& button_image : button_images) {
    buttons_.push_back(
        new MenuButton(Size(kSizeOfButton), window,
                       button_image.main_path, button_image.active_path));
    buttons_.back()->SetSecondIconPath(
        confirm.main_path, confirm.active_path);
    buttons_.back()->hide();
    int index = buttons_.size() - 1;
    auto button_click = [this, index]() {
      ButtonTapped(index);
    };
    QObject::connect(buttons_.back(), &QPushButton::clicked,
                     button_click);
  }
}

void TowerMenu::Recreate(Coordinate position, int owner_building_index,
                         const std::vector<int>& possible_buildings_id,
                         int owner_id, const SizeHandler& size_handler,
                         int total_cost) {
  if (is_hidden_) {
    return;
  }
  for (auto& id : possible_buildings_id_) {
    buttons_[id]->EnableSecondIcon(false);
    buttons_[id]->hide();
  }
  possible_buildings_id_ = possible_buildings_id;
  for (auto& id : possible_buildings_id_) {
    buttons_[id]->SetGeometry(position - kSizeOfButton / 2, size_handler);
    buttons_[id]->show();
  }
  owner_id_ = owner_id;
  owner_building_index_ = owner_building_index;
  position_ = position;
  current_force_ = kThrowForce;
  active_button_index_ = -1;
  slow_disable = false;
  id_to_replace_ = false;
  total_cost_ = total_cost;
}

void TowerMenu::Tick(const SizeHandler& size_handler, int delta_time) {
  info_field_.SetPosition(position_, button_constants::kShortButtonSize,
                          button_constants::kShift);
  if (active_button_index_ != -1) {
    info_field_.SetVisible(true);
  }
  for (auto& button : buttons_) {
    button->UpdateIcon();
  }
  if (current_force_ < 1 || possible_buildings_id_.empty()) {
    return;
  }
  if (current_force_ > 70) {
    for (auto& button : buttons_) {
      button->SetIsEnter(false);
    }
  }
  info_field_.SetVisible(false);
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
  current_force_ *= kSlowdownCoefficient;
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
        Disable();
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
  id_to_replace_ = false;
}

void TowerMenu::DrawTowersAuraAndRange(QPainter* painter,
                                       const SizeHandler& size_handler,
                                       const Building& instance) {
  if (is_hidden_) {
    return;
  }
  painter->save();
  Coordinate position = position_;
  position.y += instance.GetSize().height / 3;
  Coordinate center = size_handler.GameToWindowCoordinate(position);
  Size radius;
  int attack_range = instance.GetAttackRange();
  radius = size_handler.GameToWindowSize(Size(attack_range, attack_range));
  instance.GetAuricField().Draw(
      painter, size_handler, position);

  QRadialGradient gradient(
      center.x, center.y / constants::kSemiMinorCoefficient, radius.width);

  QColor gradient_color(Qt::darkRed);
  gradient_color.setAlpha(60);
  gradient.setColorAt(0, Qt::transparent);
  gradient.setColorAt(0.80, Qt::transparent);
  gradient.setColorAt(1, gradient_color);

  painter->setPen(Qt::transparent);
  painter->setBrush(gradient);
  painter->scale(1, constants::kSemiMinorCoefficient);
  painter->drawEllipse(QPointF(
      center.x, center.y / constants::kSemiMinorCoefficient),
                       radius.width, radius.height);

  painter->restore();
}

void TowerMenu::DrawInfoField(QPainter* painter,
                              const SizeHandler& size_handler,
                              const Building& instance) {
  if (is_hidden_) {
    return;
  }
  painter->save();

  painter->setPen(QPen(Qt::white, 3));
  for (uint i = 1; i < possible_buildings_id_.size(); i++) {
    Coordinate button_position_1 =
        buttons_[possible_buildings_id_[i - 1]]->GetPosition();
    button_position_1 += kSizeOfButton / 2;
    button_position_1 = size_handler.GameToWindowCoordinate(button_position_1);
    Coordinate button_position_2 =
        buttons_[possible_buildings_id_[i]]->GetPosition();
    button_position_2 += kSizeOfButton / 2;
    button_position_2 = size_handler.GameToWindowCoordinate(button_position_2);
    painter->drawLine(button_position_1.x, button_position_1.y,
                      button_position_2.x, button_position_2.y);
  }

  painter->restore();
  info_field_.SetInfo(instance, total_cost_);
  info_field_.Draw(painter, size_handler);
}

void TowerMenu::Hide(bool is_hidden) {
  if (is_hidden == is_hidden_) {
    return;
  }
  is_hidden_ = is_hidden;
  for (int index : possible_buildings_id_) {
    buttons_[index]->setHidden(is_hidden);
  }
}

void TowerMenu::Close() {
  slow_disable = true;
  current_force_ = kThrowForce * 1.3;
  return;
}

int TowerMenu::GetTownerIndex() const {
  return owner_building_index_;
}

int TowerMenu::GetSellectedTowerId() const {
  if (active_button_index_ == -1) {
    return owner_id_;
  }
  return active_button_index_;
}

bool TowerMenu::IsEnable() const {
  return !possible_buildings_id_.empty();
}

bool TowerMenu::IsWantToReplace() const {
  return id_to_replace_;
}

void TowerMenu::Disable() {
  slow_disable = false;
  for (auto& id : possible_buildings_id_) {
    buttons_[id]->EnableSecondIcon(false);
    buttons_[id]->hide();
  }
  possible_buildings_id_.clear();
}

