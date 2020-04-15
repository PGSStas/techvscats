#include "bomb_projectile.h"

BombProjectile::BombProjectile(const BombProjectile& other)
    : AbstractProjectile(other), effect_radius_(other.effect_radius_),
      up_force_(other.up_force_), start_position_(position_) {
}

BombProjectile::BombProjectile(Size size, double speed, double effect_radius,
                               double up_force)
    : AbstractProjectile(size, speed) {
  effect_radius_ = effect_radius;
  up_force_ = up_force;
}

void BombProjectile::Tick(int current_time) {
  UpdateTime(current_time);
  double percent =
      (position_.x - destination_.x) / (start_position_.x - destination_.x);
  qDebug() << delta_tick_time_;
  additional_draw_height_ += up_force_ * (1 - 2 * percent) *
      delta_tick_time_ / kTimeScale;
  Move();
}

void BombProjectile::Draw(QPainter* painter, const SizeHandler& handler) const {
  painter->save();
  painter->setBrush(draw_color_);
  Coordinate bomb_position = position_;
  bomb_position.y += additional_draw_height_;
  Coordinate position = handler.GameToWindowCoordinate(bomb_position);
  Size size = handler.GameToWindowSize(size_);
  painter->drawEllipse(position.x, position.y, size.width, size.height);
  painter->restore();
}

void BombProjectile::SetParameters(Coordinate position,
                                   double speed_coefficient,
                                   double damage,
                                   const std::shared_ptr<Enemy>& aim) {
  start_position_ = position;
  AbstractProjectile::SetParameters(position, speed_coefficient, damage, aim);
}

bool BombProjectile::IsInAffectedArea(const Enemy& enemy) {
  return position_.GetVectorTo(enemy.GetPosition()).GetLength()
      <= effect_radius_ + kEpsilon;
}
