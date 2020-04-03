#include "game_object.h"

Coordinate GameObject::GetPosition() const {
  return position_;
}

Size GameObject::GetSize() const {
  return size_;
}
