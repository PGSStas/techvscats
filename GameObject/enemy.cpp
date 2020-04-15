#include "enemy.h"

void Enemy::Tick(int time) {
  Move();
  player_.GetNextFrame(time);
}

void Enemy::Move() {
  if (has_reached_) {
    return;
  }
  moving_vector_ = position_.GetDistanceTo(destination_);
  if (moving_vector_.GetLength() > constants::kEpsilon) {
    moving_vector_ /= moving_vector_.GetLength();
    moving_vector_ *= speed_ * speed_coefficient_;
  }
  if ((position_ + moving_vector_).GetDistanceTo(destination_).GetLength()
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
  position_ += moving_vector_;
}

void Enemy::Draw(QPainter* painter,
                 const std::shared_ptr<SizeHandler>& size_handler) const {
  painter->save();

  painter->setPen(QColor("black"));
  Coordinate point =
      size_handler->GameToWindowCoordinate(position_ - Size(30, 30));
  Size size = size_handler->GameToWindowSize({60, 60});

  painter->translate(point.x, point.y);
  if (moving_vector_.width < 0) {
    painter->translate(size.width, size.height);
    painter->rotate(180);
  }
  painter->drawImage(QRect(0, 0, size.width, size.height),
      player_.GetCurrentFrame());

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

  player_ = enemy_instance.player_;
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

void Enemy::SetParameters(double speed) {
  speed_ = speed;
}

void Enemy::SetAnimationPlayer(const AnimationPlayer& player) {
  player_ = player;
}
