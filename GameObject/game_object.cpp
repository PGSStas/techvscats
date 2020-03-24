#include "game_object.h"

Coordinate GameObject::GetPosition() const {
  return position_;
}

GameObject::GameObject(const Coordinate& position) : position_(position) {}
