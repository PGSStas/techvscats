#include "enemy.h"

void Enemy::Tick(int current_time) {
  Move();
}

void Enemy::Move() {
  if (has_reached_) {
    return;
  }
  Size move_direction = position_.GetDistanceTo(destination_);
  if (std::abs(move_direction.GetLength()) > kEpsilon) {
    move_direction /= move_direction.GetLength();
    move_direction *= speed_ * speed_coefficient_;
  }
  if ((position_ + move_direction).GetDistanceTo(destination_).GetLength()
      >= position_.GetDistanceTo(destination_).GetLength()) {
    node_number_++;
    if (road_->IsEnd(node_number_)) {
      has_reached_ = true;
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
  position_ += move_direction;
}

void Enemy::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  painter->setPen(QColor("black"));
  Coordinate point =
      size_handler.GameToWindowCoordinate(position_ - Size(15, 15));
  Size size = size_handler.GameToWindowSize({30, 30});
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
  enemy_id_ = enemy_instance.enemy_id_;
  reward_ = enemy_instance.reward_;
  max_health_ = enemy_instance.max_health_;
  current_health_ = enemy_instance.max_health_;

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

Enemy::Enemy(const Enemy& enemy_instance) {
  *this = enemy_instance;
}

void Enemy::SetParameters(double speed) {
  speed_ = speed;
}

void Enemy::ReceiveDamage(double damage) {
  current_health_ -= damage;
  if (current_health_ <= 0) {
    is_dead_ = true;
  }
}
