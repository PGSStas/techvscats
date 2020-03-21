#include "enemy.h"

void Enemy::Tick() {
}

void Enemy::Draw(QPainter* painter) const {
}

void Enemy::SetRoad(const Road& road) {
  road_ = &road;
}

bool Enemy::IsDead() const {
  return is_dead_;
}

Enemy::Enemy(const Enemy& enemy_instance) {
  *this = enemy_instance;
}

Enemy::Enemy(Enemy* enemy_instance) {
  *this = *enemy_instance;
}

Enemy& Enemy::operator=(const Enemy& enemy_instance) {
  is_dead_ = enemy_instance.is_dead_;
  damage_ = enemy_instance.damage_;
  armor_ = enemy_instance.armor_;
  enemy_id_ = enemy_instance.enemy_id_;
  reward_ = enemy_instance.reward_;
  max_health_ = enemy_instance.max_health_;
  current_health_ = enemy_instance.max_health_;
  road_ = enemy_instance.road_;
  node_number_ = 0;
  SetPosition(road_->GetNode(node_number_));
  return *this;
}
