#include "enemy.h"

void Enemy::Tick() {
  Move();
}

void Enemy::Move() {
  if (has_reached_) {
    return;
  }
  Coordinate move_direction = position_.VectorTo(destination_);
  if (abs(move_direction.Lentgth()) > 0.0001) {
    move_direction /= move_direction.Lentgth();
    move_direction *= speed_ * speed_coefficient_;
  }

  if ((position_ + move_direction).VectorTo(destination_).Lentgth()
      >= (position_).VectorTo(destination_).Lentgth()) {
    node_number_++;
    if (road_->IsEnd(node_number_)) {
      SetHasReached(true);
      return;
    }
    destination_ = (road_->GetNode(node_number_));
  }
  SetPosition(position_ + move_direction);
}

void Enemy::Draw(QPainter* painter) const {
  const Coordinate& position = GetPosition();
  // painter->save();
  painter->setPen(QColor("black"));
  painter->drawRect(position.x - 15, position.y - 15, 30, 30);
  // painter->load();
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
  road_ = enemy_instance.road_;
  node_number_ = 0;
  if (road_ != nullptr) {
    SetRoad(*road_);
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

Enemy::Enemy(const Enemy& enemy_instance) {
  *this = enemy_instance;
}
