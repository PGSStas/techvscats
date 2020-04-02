#include "size_handler.h"

SizeHandler::SizeHandler() :
    scaling_coefficient_(3), origin_(0, 0) {}

void SizeHandler::ChangeSystem(double window_width, double window_height) {
  scaling_coefficient_ = std::max(playing_field_width_ / window_width,
                                  playing_field_height_ / window_height);

  Size real_size = Size(playing_field_width_ / scaling_coefficient_,
                        playing_field_height_ / scaling_coefficient_);

  origin_.x = (window_width - real_size.width_) / 2;
  origin_.y = (window_height - real_size.height_) / 2;
}

Coordinate SizeHandler::WindowToGameCoordinate(
    Coordinate window_coordinate) const {
  return (window_coordinate - origin_) * scaling_coefficient_;
}

Coordinate SizeHandler::GameToWindowCoordinate(
    Coordinate game_coordinate) const {
  return (game_coordinate / scaling_coefficient_) + origin_;;
}

Size SizeHandler::GameToWindowSize(Size game_size) const {
  return game_size / scaling_coefficient_;
}

Size SizeHandler::WindowToGameSize(Size window_size) const {
  return window_size * scaling_coefficient_;
}
