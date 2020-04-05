#include "game_object.h"

Coordinate GameObject::GetPosition() const {
  return position_;
}

void GameObject::SetPosition(Coordinate position) {
  position_ = position;
}

Size GameObject::GetSize() const {
  return size_;
}

GameObject::GameObject(Coordinate position) : position_(position) {}
