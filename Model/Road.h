#ifndef MODEL_ROAD_H_
#define MODEL_ROAD_H_

#include <vector>
#include "Coordinate.h"

class Road {
 public:
  // Returns the next vertex for the coordinate_num.
  // If the vertex is the last, it returns null.
  Coordinate GetNode(int direction_num);

 private:
  std::vector<Coordinate> vertex;
};

#endif  // MODEL_ROAD_H_
