#include "base.h"

const Size Base::kBaseSize = Size(50, 50);
const Coordinate Base::kHealthPosition = Coordinate(1700, 1000);
const Coordinate Base::kGoldPosition = Coordinate(1800, 1000);
const double Base::kFontSize = 22;

Base::Base(int gold, double max_health, Coordinate position)
    : GameObject(Size(0, 0), position), gold_(gold),
      max_health_(max_health), current_health_(max_health) {}

void Base::Tick(int) {
  current_health_ = std::min(max_health_, current_health_ + regeneration_rate_);
}

void Base::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  auto font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(kFontSize));
  painter->setFont(font);

  Coordinate health_top_corner =
      size_handler.GameToWindowCoordinate(kHealthPosition);
  painter->drawText(health_top_corner.x, health_top_corner.y,
                    QString::number(current_health_));

  Coordinate gold_top_corner =
      size_handler.GameToWindowCoordinate(kGoldPosition);
  painter->drawText(gold_top_corner.x, gold_top_corner.y,
                    QString::number(gold_));

  painter->setBrush(Qt::magenta);

  auto point = size_handler.GameToWindowCoordinate(position_ - kBaseSize / 2);
  Size size = size_handler.GameToWindowSize(kBaseSize);

  painter->drawRect(point.x, point.y, size.width, size.height);

  painter->restore();
}

void Base::DecreaseHealth(double damage) {
  current_health_ -= std::min(damage, current_health_);
  if (current_health_ <= kEpsilon) {
    is_dead_ = true;
  }
}

double Base::GetCurrentHealth() const {
  return current_health_;
}

double Base::GetMaxHealth() const {
  return max_health_;
}

int Base::GetGold() const {
  return gold_;
}

Coordinate Base::GetGoldPosition() const {
  return kGoldPosition;
}

void Base::AddGoldAmount(int gold_amount) {
  gold_ += gold_amount;
}

void Base::SubtractGoldAmount(int gold_amount) {
  gold_ -= gold_amount;
}

bool Base::IsDead() const {
  return is_dead_;
}
