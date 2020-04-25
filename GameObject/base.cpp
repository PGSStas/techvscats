#include "base.h"

Base::Base(Size size, Coordinate position, double max_health)
    : GameObject(size, position), max_health_(max_health),
      current_health_(max_health) {}

void Base::Tick(int current_time) {
  UpdateTime(current_time);
  current_health_ = std::min(max_health_, current_health_ + regeneration_rate_);
  double heal_percent = current_health_ / max_health_;

  int period = 0;
  if (heal_percent < 0.8) {
    period = 4000 * heal_percent;
  }
  particle_handler_.SetPeriod(period);
}

void Base::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  Coordinate point = size_handler.GameToWindowCoordinate(
      position_ - size_ / 2);
  painter->drawImage(QPoint(point.x, point.y),
                     animation_players_[0].GetCurrentFrame());

  Coordinate health_bar_top_corner =
      size_handler.GameToWindowCoordinate(kHealthBarPosition);
  Size health_bar_size =
      size_handler.GameToWindowSize({kHealthBarSize.width * current_health_
                                         / max_health_,
                                     kHealthBarSize.height});
  painter->setBrush(Qt::red);
  painter->drawRect(health_bar_top_corner.x, health_bar_top_corner.y,
                    health_bar_size.width, health_bar_size.height);

  painter->restore();
}

void Base::DecreaseHealth(double damage) {
  current_health_ -= std::min(damage, current_health_);

  Coordinate rand_position = position_;
  rand_position +=
      Size(qrand() % static_cast<int>(size_.width ) - size_.width / 2,
           qrand() % static_cast<int>(size_.height ) - size_.height / 2);
  particle_handler_.AddParticle(
      ParticleParameters(0, size_ / 3, rand_position));

  if (current_health_ <= constants::kEpsilon) {
    is_dead_ = true;
  }
}

double Base::GetCurrentHealth() const {
  return current_health_;
}

double Base::GetMaxHealth() const {
  return max_health_;
}
bool Base::IsDead() const {
  return is_dead_;
}
