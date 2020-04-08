#include "game_object.h"

GameObject::GameObject(Coordinate position, Size size)
    : position_(position), size_(size) {}

Coordinate GameObject::GetPosition() const {
  return position_;
}

void GameObject::SetPosition(Coordinate position) {
  position_ = position;
}

Size GameObject::GetSize() const {
  return size_;
}

void GameObject::SetSize(Size size) {
  size_ = size;
}
