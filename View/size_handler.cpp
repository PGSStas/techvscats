#include "size_handler.h"

SizeHandler::SizeHandler() {
  zero_coordinate_ = Coordinate(0, 0);
  change_coefficient_ = 3;
}

void SizeHandler::ChangeSystem(double window_width, double window_height) {
  change_coefficient_ = std::max(playing_field_width_ / window_width,
                                 playing_field_height_ / window_height);

  QSize real_size = QSize(playing_field_width_ / change_coefficient_,
                          playing_field_height_ / change_coefficient_);

  zero_coordinate_ = {0, 0};
  double indent;
  if (window_width > real_size.width()) {
    indent = (window_width - real_size.width()) / 2.;
    zero_coordinate_.x = indent;
  }
  if (window_height > real_size.height()) {
    indent = (window_height - real_size.height()) / 2.;
    zero_coordinate_.y = indent;
  }
}

Coordinate SizeHandler::ToGame(const Coordinate& window_coordinate) const {
  Coordinate game_coordinate =
      (window_coordinate - zero_coordinate_) * change_coefficient_;
  return game_coordinate;
}

Coordinate SizeHandler::ToWindow(const Coordinate& game_coordinate) const {
  Coordinate window_coordinate =
      (game_coordinate / change_coefficient_) + zero_coordinate_;
  return window_coordinate;
}

Coordinate SizeHandler::SizeToWindowSize(double width, double height) const {
  return Coordinate(width / change_coefficient_, height / change_coefficient_);
}

Coordinate SizeHandler::SizeToGameSize(double width, double height) const {
  return Coordinate(width * change_coefficient_, height * change_coefficient_);
}
