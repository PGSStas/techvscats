#include "game_object.h"

Coordinate GameObject::GetPosition() const {
  return position_;
}

void GameObject::SetPosition(const Coordinate& position) {
  position_ = position;
}
