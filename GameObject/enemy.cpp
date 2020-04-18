#include "enemy.h"

std::mt19937 Enemy::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

Enemy::Enemy(Size size, double speed, double damage, double armor, int reward,
             double max_health, AuricField auric_field)
    : MovingObject(size, speed), damage_(damage), armor_(armor),
      reward_(reward), max_health_(max_health), auric_field_(auric_field) {
  auric_field.SetCarrierCoordinate(&position_);
}

Enemy::Enemy(const Enemy& enemy_instance)
    : MovingObject(enemy_instance.GetSize(), enemy_instance.speed_),
      damage_(enemy_instance.damage_), armor_(enemy_instance.armor_),
      reward_(enemy_instance.reward_), max_health_(enemy_instance.max_health_),
      current_health_(enemy_instance.max_health_),
      auric_field_(enemy_instance.auric_field_) {
  auric_field_.SetCarrierCoordinate(&position_);
  node_number_ = 0;
  if (enemy_instance.road_ != nullptr) {
    SetRoad(*enemy_instance.road_);
  }
  player_ = enemy_instance.player_;
}

void Enemy::Tick(int current_time) {
  UpdateTime(current_time);
  Move();
  player_.GetNextFrame(current_time);
}

void Enemy::Move() {
  if (is_end_reached_) {
    return;
  }

  MoveToDestination();
  if (position_ == destination_) {
    node_number_++;
    if (road_->IsEnd(node_number_)) {
      is_end_reached_ = true;
      return;
    }
    destination_ = (road_->GetNode(node_number_));
    if (!road_->IsEnd(node_number_ + 1)) {
      // We make small shifts so that enemies move chaotically,
      // not in the linear queue
      destination_.x += static_cast<int32_t>(random_generator_()) % kMoveShift
          - kMoveShift / 2;
      destination_.y += static_cast<int32_t>(random_generator_()) % kMoveShift
          - kMoveShift / 2;
    }
  }
}

void Enemy::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  Coordinate point =
      size_handler.GameToWindowCoordinate(position_ - Size(30, 30));
  Size size = size_handler.GameToWindowSize({60, 60});

  painter->translate(point.x, point.y);
  if (moving_vector_.width < 0) {
    painter->translate(size.width, 0);
    // mirroring the image
    painter->scale(-1.0, 1.0);
  }
  painter->drawImage(QRect(0, 0, size.width, size.height),
      player_.GetCurrentFrame());

  painter->restore();
}

void Enemy::DrawHealthBar(QPainter* painter,
                          const SizeHandler& size_handler) const {
  painter->save();

  painter->setBrush(Qt::red);
  Coordinate point =
      size_handler.GameToWindowCoordinate(position_ - kHealthBarShift);
  Size size = size_handler.GameToWindowSize(Size(
      kHealthBar.width * current_health_ / max_health_, kHealthBar.height));
  painter->drawRect(point.x, point.y, size.width, size.height);

  painter->restore();
}

void Enemy::SetRoad(const Road& road) {
  road_ = std::make_shared<const Road>(road);
  position_ = road_->GetNode(node_number_);
  destination_ = road_->GetNode(node_number_);
}
const AuricField& Enemy::GetAuricField() const {
  return auric_field_;
}

Effect* Enemy::GetAppliedEffect() {
  return &applied_effect_;
}

double Enemy::GetDamage() const {
  return damage_ * applied_effect_.GetDamageCoefficient();
}

void Enemy::ReceiveDamage(double damage) {
  // Temporary formula.
  double armor = armor_ * applied_effect_.GetArmorCoefficient();
  double multiplier = 1 - ((0.052 * armor) / (0.9 + 0.048 * std::abs(armor)));
  current_health_ -= std::min(multiplier * damage, current_health_);
  if (current_health_ <= constants::kEpsilon) {
    is_dead_ = true;
  }
}

void Enemy::SetAnimationPlayer(const AnimationPlayer& player) {
  player_ = player;
}
