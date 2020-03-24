#include "size_handler.h"

SizeHandler::SizeHandler(QMainWindow* view) : view_(view) {

  view_->setMinimumSize(1280, 720);
  zero_coordinate_ = Coordinate(0, 0);
  change_coefficient_ = 1.5;
}

void SizeHandler::ChangeSystem() {
  QSize window_size = view_->size();
  change_coefficient_ =
      std::max(1080./window_size.height(), 1920. / window_size.width());
  QSize real_size = QSize(1920. / change_coefficient_,
                          1080. / change_coefficient_);
  if (window_size.width() > real_size.width()) {
    int indent = (window_size.width() - real_size.width())/2;
    zero_coordinate_.x = indent;
    zero_coordinate_.y = 0;
  } else if (window_size.height() > real_size.height()) {
    int indent = (window_size.height() - real_size.height())/2;
    zero_coordinate_.y = indent;
    zero_coordinate_.x = 0;
  } else {
    zero_coordinate_.x = 0;
    zero_coordinate_.y = 0;
  }
  // qDebug() << zero_coordinate_.x << " " << zero_coordinate_.y;
}

Coordinate SizeHandler::ToGame(const Coordinate& window_coord) {
  Coordinate game_coord;
  game_coord.x = (window_coord.x - zero_coordinate_.x) * change_coefficient_;
  game_coord.y = (window_coord.y - zero_coordinate_.y) * change_coefficient_;
  return game_coord;
}

Coordinate SizeHandler::ToWindow(const Coordinate& game_coord) {
  Coordinate window_coord;
  window_coord.x = (game_coord.x + zero_coordinate_.x) / change_coefficient_;
  window_coord.y = (game_coord.y + zero_coordinate_.y) / change_coefficient_;
  return window_coord;
}
