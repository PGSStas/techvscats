#include "base.h"

std::mt19937 Base::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

Base::Base(int gold, Size size, Coordinate position, double max_health)
    : GameObject(size, position), gold_(gold), max_health_(max_health),
      current_health_(max_health) {}

void Base::Tick(int current_time) {
  UpdateTime(current_time);
  animation_players_[0].Tick(delta_time_);
  current_health_ = std::min(max_health_, current_health_ + regeneration_rate_);
  int period = 0;
  double health_percent = current_health_ / max_health_;
  if (health_percent < 0.8) {
    period = 4000 * health_percent;
  }
  particle_handler_.SetPeriod(period);
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

  Coordinate point = size_handler.GameToWindowCoordinate(
      position_ - size_ / 2);
  painter->drawImage(point.x, point.y, animation_players_[0].GetCurrentFrame());

  painter->restore();
}

void Base::DecreaseHealth(double damage) {
  current_health_ -= std::min(damage, current_health_);

  Coordinate rand_position = position_;
  rand_position +=
      Size(random_generator_() % static_cast<int>(size_.width)
               - size_.width / 2,
           random_generator_() % static_cast<int>(size_.height)
               - size_.height / 2);
  particle_handler_.AddParticle(
      ParticleParameters(0, size_ / 3, rand_position));

  if (current_health_ <= constants::kEpsilon) {
    is_dead_ = true;
  }
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
