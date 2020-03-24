#include "size_handler.h"

SizeHandler::SizeHandler(QMainWindow* view) : view_(view) {

  view_->setMinimumSize(playing_field_width_ / 3, playing_field_height_ / 3);
  zero_coordinate_ = Coordinate(0, 0);
  change_coefficient_ = 3;
}

void SizeHandler::ChangeSystem() {
  QSize window_size = view_->size();
  change_coefficient_ = std::max(playing_field_width_ / window_size.width(),
                                 playing_field_height_ / window_size.height());

  QSize real_size = QSize(playing_field_width_ / change_coefficient_,
                          playing_field_height_ / change_coefficient_);

  zero_coordinate_.x = 0;
  zero_coordinate_.y = 0;
  double indent;
  if (window_size.width() > real_size.width()) {
    indent = (window_size.width() - real_size.width()) / 2.;
    zero_coordinate_.x = indent;
  }
  if (window_size.height() > real_size.height()) {
    indent = (window_size.height() - real_size.height()) / 2.;
    zero_coordinate_.y = indent;
  }
}

Coordinate SizeHandler::ToGame(const Coordinate& window_coord) {
  Coordinate game_coord;
  game_coord.x = (window_coord.x - zero_coordinate_.x) * change_coefficient_;
  game_coord.y = (window_coord.y - zero_coordinate_.y) * change_coefficient_;
  return game_coord;
}

Coordinate SizeHandler::ToWindow(const Coordinate& game_coord) {
  Coordinate window_coord;
  window_coord.x = (game_coord.x / change_coefficient_) + zero_coordinate_.x;
  window_coord.y = (game_coord.y / change_coefficient_) + zero_coordinate_.y;
  return window_coord;
}

Coordinate SizeHandler::ToGame(double position_x, double position_y) {
  return ToGame(Coordinate(position_x, position_y));
}

Coordinate SizeHandler::ToWindow(double position_x, double position_y) {
  return ToWindow(Coordinate(position_x, position_y));
}

Coordinate SizeHandler::SizeToWindowSize(double width, double height) {
  return Coordinate(width / change_coefficient_, height / change_coefficient_);
}

Coordinate SizeHandler::SizeToGameSize(double width, double height) {
  return Coordinate(width * change_coefficient_, height * change_coefficient_);
}

void SizeHandler::SetPlayingFieldSize(double width, double height) {
  playing_field_width_ = width;
  playing_field_height_ = height;
}
