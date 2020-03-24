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
  Coordinate ToWindow(const Coordinate& game_coord);

 private:
  QMainWindow* view_;
  Coordinate zero_coordinate_;
  double change_coefficient_;
};

#endif  // VIEW_GAME_HANDLER_H_
