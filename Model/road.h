#ifndef MODEL_ROAD_H_
#define MODEL_ROAD_H_

#include <vector>
#include "coordinate.h"

class Road {
 public:
  // Returns the next vertex for the coordinate_num.
  // If the vertex is the last, it returns null.
  explicit Road(std::vector<Coordinate> nodes);
  Coordinate GetNode(int node_number);

 private:
  std::vector<Coordinate> nodes_;
};

#endif  // MODEL_ROAD_H_
