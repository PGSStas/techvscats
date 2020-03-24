#ifndef  VIEW_GAME_HANDLER_H_
#define  VIEW_GAME_HANDLER_H_

#include <QMainWindow>
#include <QDebug>
#include "Model/coordinate.h"
class SizeHandler {
 public:
  explicit SizeHandler(QMainWindow* view);

  void ChangeSystem();

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
};

#endif  // VIEW_GAME_HANDLER_H_
