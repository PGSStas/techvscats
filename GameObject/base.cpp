#include "base.h"

Base::Base(double max_health)
    : max_health_(max_health),
      current_health_(max_health),
      is_dead_(false) {}

bool Base::IsDead() const {
  return is_dead_;
}

void Base::DecreaseHealth(double damage) {
  current_health_ -= std::min(damage, current_health_);
  if (current_health_ == 0) {
    is_dead_ = true;
  }
}

double Base::GetCurrentHealth() const {
  return current_health_;
}

double Base::GetMaxHealth() const {
  return max_health_;
}

void Base::Draw(QPainter* painter,
                const std::shared_ptr<SizeHandler>& size_handler) const {
  painter->save();

  painter->setBrush(Qt::magenta);

  int n = positions_.size();
  for (int i = 0; i < n; i++) {
    Coordinate point =
        size_handler->GameToWindowCoordinate(positions_[i] - kBaseSize / 2);
    Size size = size_handler->GameToWindowSize(kBaseSize);

    painter->drawRect(point.x, point.y, size.width, size.height);
  }

  Coordinate health_bar_top_corner =
      size_handler->GameToWindowCoordinate(kHealthBarPosition);
  Size health_bar_size =
      size_handler->GameToWindowSize({kHealthBarSize.width * current_health_
                                          / max_health_,
                                      kHealthBarSize.height});
  painter->setBrush(Qt::red);
  painter->drawRect(health_bar_top_corner.x,
                    health_bar_top_corner.y,
                    health_bar_size.width,
                    health_bar_size.height);

  painter->restore();
}

void Base::Tick() {
  current_health_ = std::min(max_health_, current_health_ + regeneration_rate_);
}

void Base::SetPositions(const std::vector<Coordinate>& positions) {
  positions_ = positions;
}

Base& Base::operator=(const Base& other) {
  regeneration_rate_ = other.regeneration_rate_;
  max_health_ = other.max_health_;
  current_health_ = max_health_;
}
