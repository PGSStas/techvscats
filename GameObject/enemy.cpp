#include "enemy.h"

void Enemy::Tick() {
  Move();
}

void Enemy::Move() {
  if (has_reached_) {
    return;
  }
  Coordinate move_direction = position_.GetBetween(destination_);
  if (abs(move_direction.GetLength()) > 0.0001) {
    move_direction /= move_direction.GetLength();
    move_direction *= speed_ * speed_coefficient_;
  }
  if ((position_ + move_direction).GetBetween(destination_).GetLength()
      >= (position_).GetBetween(destination_).GetLength()) {
    node_number_++;
    if (road_->IsEnd(node_number_)) {
      has_reached_ = true;
      return;
    }
    destination_ = (road_->GetNode(node_number_));
  }
  position_ += move_direction;
}

void Enemy::Draw(QPainter* painter,
                 std::shared_ptr<SizeHandler> size_handler) const {
  painter->save();

  painter->setPen(QColor("black"));
  painter->drawRect(size_handler->ToWindow(position_ - Coordinate(15, 15)).x,
                    size_handler->ToWindow(position_ - Coordinate(15, 15)).y,
                    size_handler->SizeToWindowSize(30, 30).x,
                    size_handler->SizeToWindowSize(30, 30).y);

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

bool Enemy::IsDead() const {
  return is_dead_;
}

Enemy::Enemy(const Enemy& enemy_instance) {
  *this = enemy_instance;
}

void Enemy::SetParametres(double speed) {
  speed_ = speed;
}
