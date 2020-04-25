#include "enemy.h"

std::mt19937 Enemy::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

Enemy::Enemy(double speed, double damage, double armor, int reward,
             double max_health, Size size, AuricField auric_field)
    : MovingObject(size, speed), damage_(damage), armor_(armor),
      reward_(reward), max_health_(max_health), current_health_(max_health_),
      auric_field_(auric_field), node_number_(0) {
}

Enemy::Enemy(const Enemy& other)
    : Enemy(other.speed_, other.damage_, other.armor_,
            other.reward_, other.max_health_, other.size_, other.auric_field_) {
  SetAnimationPlayers(other.animation_players_);
  particle_handler_.SetParticlePacks(other.particle_handler_);
  auric_field_.SetCarrierCoordinate(&position_);
  if (other.road_ != nullptr) {
    SetRoad(*other.road_);
  }
}

void Enemy::Tick(int current_time) {
  UpdateTime(current_time);
  Move();
  animation_players_[0].Tick(delta_time_ *
      applied_effect_.GetMoveSpeedCoefficient());
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

  Coordinate point = size_handler.GameToWindowCoordinate(
      position_ - size_ / 2);
  Size size = size_handler.GameToWindowSize(size_);

  painter->translate(point.x, point.y);
  if (position_.GetVectorTo(destination_).width < constants::kEpsilon) {
    painter->translate(size.width, 0);
    // mirroring the image
    painter->scale(-1.0, 1.0);
  }
  painter->drawImage(QPoint(0, 0), animation_players_[0].GetCurrentFrame());

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

Coordinate Enemy::GetPrefirePosition() const {
  Size move_vector = position_.GetVectorTo(destination_);
  move_vector /= move_vector.GetLength();
  Coordinate prefire_position = position_;
  prefire_position +=
      move_vector * speed_ * applied_effect_.GetMoveSpeedCoefficient()
          * constants::kTimeScale/delta_time_;
  return prefire_position;
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
    particle_handler_.CarrierDeath();
    is_dead_ = true;
  }
}
