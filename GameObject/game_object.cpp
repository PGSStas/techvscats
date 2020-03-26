#include "game_object.h"

Coordinate GameObject::GetPosition() const {
  return position_;
}

GameObject::GameObject(Coordinate pos) : position_(pos) {}

void GameObject::SetPosition(Coordinate pos) { position_ = pos; }