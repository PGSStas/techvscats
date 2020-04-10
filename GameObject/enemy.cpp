#include "enemy.h"

void Enemy::Tick() {
  Move();
}

void Enemy::Move() {
  if (is_end_reached_) {
    return;
  }
  position_.MoveTo(destination_, speed_ * effect_.GetSpeedCoefficient());

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
      destination_.x += std::rand() % kMoveShift_ - kMoveShift_ / 2;
      destination_.y += std::rand() % kMoveShift_ - kMoveShift_ / 2;
    }
  }
}

void Enemy::Draw(QPainter* painter,
                 const std::shared_ptr<SizeHandler>& size_handler) const {
  painter->save();

  painter->setPen(QColor("black"));
  Coordinate point =
      size_handler->GameToWindowCoordinate(position_ - Size(15, 15));

  Size size = size_handler->GameToWindowSize({30, 30});
  painter->drawRect(point.x, point.y, size.width, size.height);

  painter->restore();
}

Enemy& Enemy::operator=(const Enemy& enemy_instance) {
  if (this == &enemy_instance) {
    return *this;
  }
  is_dead_ = enemy_instance.is_dead_;
  damage_ = enemy_instance.damage_;
  armor_ = enemy_instance.armor_;
  reward_ = enemy_instance.reward_;
  max_health_ = enemy_instance.max_health_;
  current_health_ = enemy_instance.max_health_;
  auric_field_ = enemy_instance.auric_field_;
  auric_field_.SetCarrierCoordinate(&position_);

  speed_ = enemy_instance.speed_;
  node_number_ = 0;
  if (enemy_instance.road_ != nullptr) {
    SetRoad(*enemy_instance.road_);
  }
  return *this;
}

void Enemy::SetRoad(const Road& road) {
  road_ = std::make_shared<const Road>(road);
  position_ = road_->GetNode(node_number_);
  destination_ = road_->GetNode(node_number_);
}

bool Enemy::IsDead() const {
  return is_dead_;
}

Enemy::Enemy(const Enemy& enemy_instance) : MovingObject(enemy_instance) {
  *this = enemy_instance;
}

void Enemy::ReceiveDamage(double damage) {
  // Temporary formula.
  double armor = armor_ * effect_.GetArmorCoefficient();
  double multiplier = 1 - ((0.052 * armor) / (0.9 + 0.048 * std::abs(armor)));
  current_health_ -= std::min(multiplier * damage, current_health_);
  if (current_health_ <= kEpsilon) {
    is_dead_ = true;
  }
}

double Enemy::GetDamage() const {
  return damage_ * effect_.GetDamageCoefficient();
}

void Enemy::DrawHealthBar(QPainter* painter,
                          std::shared_ptr<SizeHandler> size_handler) const {
  painter->save();

  painter->setBrush(Qt::red);
  Coordinate point =
      size_handler->GameToWindowCoordinate(position_ - Size(18, 24));
  Size size =
      size_handler->GameToWindowSize(Size(36 * current_health_ / max_health_,
                                          5));
  painter->drawRect(point.x, point.y, size.width, size.height);

  painter->restore();
}

AuricField* Enemy::GetAuricField() {
  return &auric_field_;
}

Effect* Enemy::GetEffect() {
  return &effect_;
}

Enemy::Enemy(double damage,
             double armor,
             int reward,
             double speed,
             double max_health)
    : damage_(damage),
      armor_(armor),
      reward_(reward),
      max_health_(max_health) {
  speed_ = speed;
}
