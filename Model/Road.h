#ifndef MODEL_ROAD_H_
#define MODEL_ROAD_H_

#include <vector>
#include "Coordinate.h"
class Road {
 public:
  Coordinate GetNextNode(int direction_num);

 private:
  std::vector<Coordinate> direction_points_;
};

#endif  // MODEL_ROAD_H_
