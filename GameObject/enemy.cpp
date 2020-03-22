#include "enemy.h"

void Enemy::Tick() {
  Move();
}

void Enemy::Move() {
  if (GetIsReached()) {
    return;
  }
  Coordinate move_direction = position_.VectorTo(destination_);
  if (abs(move_direction.Lentgth()) > 0.0001) {
    move_direction /= move_direction.Lentgth();
    move_direction *= speed_ * speed_;
  }

  if ((position_ + move_direction).VectorTo(destination_).Lentgth()
      >= (position_).VectorTo(destination_).Lentgth()) {
    if (road_->IsEnd(++node_number_)) {
      SetIsReached(true);
      return;
    }
    destination_ = (road_->GetNode(node_number_));

    Move();
  }
  SetPosition(position_ + move_direction);
}

void Enemy::Draw(QPainter* painter) const {
  const Coordinate& position = GetPosition();
  //painter->save();
  painter->setPen(QColor("black"));
  painter->drawRect(position.x, position.y, 30, 30);
  //painter->load();
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
    position_ = road_->GetNode(node_number_);
    road_->GetNode(node_number_);
  }
  return *this;
}

void Enemy::SetRoad(const Road& road) {
  road_ = std::make_shared<const Road>(road);
}

bool Enemy::IsDead() const {
  return is_dead_;
}

Enemy::Enemy(const Enemy& enemy_instance) {
  *this = enemy_instance;
}
