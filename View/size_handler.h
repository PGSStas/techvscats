#ifndef  VIEW_SIZE_HANDLER_H_
#define  VIEW_SIZE_HANDLER_H_

#include <QMainWindow>
#include <QDebug>
#include <algorithm>
#include "Model/coordinate.h"

class SizeHandler {
 public:
  explicit SizeHandler(QMainWindow* view);

  void ChangeSystem();
  void SetPlayingFieldSize(double width, double height);

  Coordinate ToGame(const Coordinate& window_coord);
  Coordinate ToGame(double position_x, double position_y);
  Coordinate ToWindow(const Coordinate& game_coord);
  Coordinate ToWindow(double position_x, double position_y);
  Coordinate SizeToWindowSize(double width, double height);
  Coordinate SizeToGameSize(double width, double height);

 private:
  QMainWindow* view_;
  Coordinate zero_coordinate_;
  double change_coefficient_;
  double playing_field_width_ = 1920;
  double playing_field_height_ = 1080;
};

#endif  // VIEW_SIZE_HANDLER_H_
