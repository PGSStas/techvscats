#include "size_handler.h"

SizeHandler::SizeHandler() :
    zero_coordinate_({0, 0}), change_coefficient_(3) {}

void SizeHandler::ChangeSystem(double window_width, double window_height) {
  change_coefficient_ = std::max(playing_field_width_ / window_width,
                                 playing_field_height_ / window_height);

  QSize real_size = QSize(playing_field_width_ / change_coefficient_,
                          playing_field_height_ / change_coefficient_);

  zero_coordinate_ = Coordinate(0, 0);
  if (window_width > real_size.width()) {
    zero_coordinate_.x = (window_width - real_size.width()) / 2.;
  }
  if (window_height > real_size.height()) {
    zero_coordinate_.y = (window_height - real_size.height()) / 2.;
  }
}

Coordinate SizeHandler::WindowToGameCoordinate(const Coordinate& window_coordinate) const {
  Coordinate game_coordinate =
      (window_coordinate - zero_coordinate_) * change_coefficient_;
  return game_coordinate;
}

Coordinate SizeHandler::GameToWindowCoordinate(const Coordinate& game_coordinate) const {
  Coordinate window_coordinate =
      (game_coordinate / change_coefficient_) + zero_coordinate_;
  return window_coordinate;
}

Coordinate SizeHandler::GameToWindowSize(double width, double height) const {
  return Coordinate(width, height) / change_coefficient_;
}

Coordinate SizeHandler::WindowToGameSize(double width, double height) const {
  return Coordinate(width, height) * change_coefficient_;
}
