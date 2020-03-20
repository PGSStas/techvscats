#include "enemy.h"

void Enemy::Tick() {
}

void Enemy::Draw(QPainter* painter) {
}

void Enemy::SetRoad(Road* road) {
  road_ = road;
}
bool Enemy::IsDead() {
  return is_dead_;
}
