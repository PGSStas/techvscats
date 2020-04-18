#ifndef  VIEW_SIZE_HANDLER_H_
#define  VIEW_SIZE_HANDLER_H_

#include <algorithm>
#include <QDebug>
#include <QMainWindow>

#include "Model/coordinate.h"
#include "Model/size.h"

class SizeHandler {
 public:
  void ChangeSystem(double window_width, double window_height);

  Coordinate WindowToGameCoordinate(Coordinate window_coordinate) const;
  Coordinate GameToWindowCoordinate(Coordinate game_coordinate) const;
  Size WindowToGameSize(Size window_size) const;
  Size GameToWindowSize(Size game_size) const;
  double GameToWindowLength(double game_length) const;

 private:
  Size origin_offset_ = {0, 0};
  // The ratio of game coordinates to real
  double scaling_coefficient_ = 3;
  const double game_width_ = kGameWidth;
  const double game_height_ = kGameHeight;
};

#endif  // VIEW_SIZE_HANDLER_H_
