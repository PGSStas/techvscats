#include "size_handler.h"

SizeHandler::SizeHandler() :
    scaling_coefficient_(3), origin_offset_(0, 0) {}

void SizeHandler::ChangeSystem(double window_width, double window_height) {
  scaling_coefficient_ = std::max(game_width_ / window_width,
                                  game_height_ / window_height);

  Size real_size = Size(game_width_ / scaling_coefficient_,
                        game_height_ / scaling_coefficient_);

  origin_offset_.width = (window_width - real_size.width) / 2;
  origin_offset_.height = (window_height - real_size.height) / 2;
}

Coordinate SizeHandler::WindowToGameCoordinate(
    Coordinate window_coordinate) const {
  return (window_coordinate - origin_offset_) * scaling_coefficient_;
}

Coordinate SizeHandler::GameToWindowCoordinate(
    Coordinate game_coordinate) const {
  return (game_coordinate / scaling_coefficient_) + origin_offset_;
}

Size SizeHandler::GameToWindowSize(Size game_size) const {
  return game_size / scaling_coefficient_;
}

Size SizeHandler::WindowToGameSize(Size window_size) const {
  return window_size * scaling_coefficient_;
}
