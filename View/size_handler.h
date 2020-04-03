#ifndef  VIEW_SIZE_HANDLER_H_
#define  VIEW_SIZE_HANDLER_H_

#include <QMainWindow>
#include <QDebug>
#include <algorithm>

#include "Model/coordinate.h"
#include "Model/size.h"

class SizeHandler {
 public:
  SizeHandler();

  void ChangeSystem(double window_width, double window_height);

  Coordinate WindowToGameCoordinate(Coordinate window_coordinate) const;
  Coordinate GameToWindowCoordinate(Coordinate game_coordinate) const;
  Size WindowToGameSize(Size window_size) const;
  Size GameToWindowSize(Size game_size) const;

 private:
  // The ratio of game coordinates to real
  double scaling_coefficient_;

  Size origin_offset_;

  const double game_width_ = 1920;
  const double game_height_ = 1080;
};

#endif  // VIEW_SIZE_HANDLER_H_
