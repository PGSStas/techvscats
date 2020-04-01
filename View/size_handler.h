#ifndef  VIEW_SIZE_HANDLER_H_
#define  VIEW_SIZE_HANDLER_H_

#include <QMainWindow>
#include <QDebug>
#include <algorithm>
#include "Model/coordinate.h"

class SizeHandler {
 public:
  SizeHandler();

  void ChangeSystem(double window_width, double window_height);

  Coordinate WindowToGameCoordinate(const Coordinate& window_coordinate) const;
  Coordinate GameToWindowCoordinate(const Coordinate& game_coordinate) const;
  Coordinate WindowToGameSize(double width, double height) const;
  Coordinate GameToWindowSize(double width, double height) const;

 private:
  // The ratio of game coordinates to real
  double change_coefficient_;

  Coordinate coordinate_origin_;

  const double playing_field_width_ = 1920;
  const double playing_field_height_ = 1080;
};

#endif  // VIEW_SIZE_HANDLER_H_
