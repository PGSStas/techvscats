#include "bomb_projectile.h"

BombProjectile::BombProjectile(Size size, double speed, double effect_radius,
                               double up_force)
    : AbstractProjectile(size, speed),
      effect_radius_(effect_radius), up_force_(up_force) {}

BombProjectile::BombProjectile(const BombProjectile& other)
    : AbstractProjectile(other), effect_radius_(other.effect_radius_),
      up_force_(other.up_force_), start_position_(position_) {
}

void BombProjectile::Tick(int current_time) {
  UpdateTime(current_time);
  double percent = (position_.x - destination_.x) /
      (start_position_.x - destination_.x);
  additional_draw_height_ += up_force_ * (1 - 2 * percent) *
      delta_time_ / constants::kTimeScale;
  Move();
  animation_players_[0].Tick(delta_time_);
}

void BombProjectile::Draw(QPainter* painter, const SizeHandler& handler) const {
  painter->save();

  Coordinate bomb_position = position_;
  bomb_position.y += additional_draw_height_;
  Coordinate point = handler.GameToWindowCoordinate(
      bomb_position - size_ / 2);

  painter->translate(point.x, point.y);
  painter->drawImage(QPoint(0, 0), animation_players_[0].GetCurrentFrame());
  painter->restore();
}

void BombProjectile::SetParameters(const std::shared_ptr<Enemy>& aim,
                                   Coordinate position,
                                   double speed_coefficient, double damage) {
  start_position_ = position;
  AbstractProjectile::SetParameters(aim, position, speed_coefficient, damage);
  destination_ = aim_->GetPrefirePosition();
}

bool BombProjectile::IsInAffectedArea(const Enemy& enemy) {
  return position_.GetVectorTo(enemy.GetPosition()).GetLength()
      <= effect_radius_ + constants::kEpsilon;
}
