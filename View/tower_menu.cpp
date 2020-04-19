#include "tower_menu.h"

#include <utility>

TowerMenu::TowerMenu(int creation_time, const Building& tower,
                     std::vector<std::shared_ptr<TowerMenuOption>> options) :
    options_(std::move(options)), tower_(tower), creation_time_(creation_time) {
  container_length_ = options_[0]->GetMaxSize() * options_.size() +
      kIndentBetweenButtons * (options_.size() - 1);
}

void TowerMenu::Hover(const std::shared_ptr<TowerMenuOption>& option) {
  hovered_option_ = option;
}

void TowerMenu::Draw(QPainter* painter,
                     const SizeHandler& size_handler, int current_time) const {
  painter->save();
  Coordinate center = size_handler.GameToWindowCoordinate(
      tower_.GetPosition());
  tower_.GetAuricField().Draw(painter, size_handler);
  Size radius;
  if (hovered_option_ == nullptr) {
    radius = size_handler.GameToWindowSize(
        Size(tower_.GetAttackRange(), tower_.GetAttackRange()));
  } else {
    radius = size_handler.GameToWindowSize(
        Size(hovered_option_->GetReplacingTower().GetAttackRange(),
             hovered_option_->GetReplacingTower().GetAttackRange()));
  }

  painter->save();
  QRadialGradient gradient(
      center.x, center.y * 1 / kSemiMinorCoefficient, radius.width);

  QColor gradient_color(Qt::yellow);
  gradient_color.setAlpha(60);
  gradient.setColorAt(0, Qt::transparent);
  gradient.setColorAt(0.80, Qt::transparent);
  gradient.setColorAt(1, gradient_color);

  painter->setPen(Qt::transparent);
  painter->setBrush(gradient);
  painter->scale(1, kSemiMinorCoefficient);
  painter->drawEllipse(QPointF(
      center.x, center.y * 1 / kSemiMinorCoefficient),
                       radius.width, radius.height);
  painter->restore();

  int time_delta = std::min(current_time - creation_time_, kAnimationDuration);
  int button_size = (time_delta * 1.0 / kAnimationDuration) *
      options_[0]->GetMaxSize();
  Size window_button_size = size_handler.GameToWindowSize(
      Size(button_size, button_size));
  for (size_t i = 0; i < options_.size(); i++) {
    options_[i]->Draw(painter, size_handler.GameToWindowCoordinate(
        CalculateCoordinate(i, button_size)), window_button_size);
  }
  painter->restore();
}

std::shared_ptr<TowerMenuOption> TowerMenu::GetButtonInside(
    Coordinate position) const {
  for (size_t i = 0; i < options_.size(); i++) {
    if (options_[i]->IsPressed(CalculateCoordinate(
        i, options_[i]->GetMaxSize()), position)) {
      return options_[i];
    }
  }
  return nullptr;
}

const Building& TowerMenu::GetTower() const {
  return tower_;
}

Coordinate TowerMenu::CalculateCoordinate(int i, int size) const {
  int x = tower_.GetPosition().x - container_length_ / 2 + i *
      options_[i]->GetMaxSize() + i * kIndentBetweenButtons +
      (options_[i]->GetMaxSize() - size) / 2;
  int y = tower_.GetPosition().y + tower_.GetSize().height / 2
      + kIndentFromTower + (options_[i]->GetMaxSize() - size) / 2;
  return Coordinate(x, y);
}
