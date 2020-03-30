#include "game_object.h"

Coordinate GameObject::GetPosition() const {
  return position_;
}

void GameObject::SetPosition(Coordinate position) {
  position_ = position;
}

bool GameObject::IsDead() const {
  return is_dead_;
}

GameObject::GameObject(Coordinate position) : position_(position) {}
