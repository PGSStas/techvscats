#include "enemy.h"

void Enemy::Tick(int current_time) {
  SetCurrentTime(current_time);
  Move();
}

void Enemy::Draw(QPainter* painter) const {
  const Coordinate& position = GetPosition();
  //painter->save();
  painter->setPen(QColor("black"));
  painter->drawRect(position.x, position.y, 30, 30);
  //painter->load();
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
  road_ = enemy_instance.road_;
  node_number_ = 0;
  SetSpeed(enemy_instance.GetSpeed());
  if (road_ != nullptr) {
    SetPosition(road_->GetNode(node_number_));
    SetDestination(road_->GetNode(node_number_));
  }
  return *this;
}


void Enemy::Move() {
  if (GetIsReached()) {
    return;
  }

  Coordinate destination = GetDestination();
  Coordinate position = GetPosition();
  Coordinate move_direction = position.VectorTo(destination);
  if (abs(move_direction.Lentgth()) > 0.0001) {
    move_direction /= move_direction.Lentgth();
    move_direction *= GetSpeed();
  }

  if ((position + move_direction).VectorTo(destination).Lentgth()
      >= (position).VectorTo(destination).Lentgth()) {
    if (road_->IsEnd(++node_number_)) {
      SetIsReached(true);
      return;
    }
    SetDestination(road_->GetNode(node_number_));
    qDebug()<<"dest : "<<GetDestination().x<<" "<<GetDestination().y;

    Move();
  }
  SetPosition(position + move_direction);
}


