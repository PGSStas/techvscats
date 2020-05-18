#ifndef MODEL_ROAD_H_
#define MODEL_ROAD_H_

#include <vector>
#include <utility>

#include "coordinate.h"

class Road {
 public:
  explicit Road(std::vector<Coordinate> nodes);

  Coordinate GetNode(int node_number) const;
  bool IsEnd(int node_number) const;

 private:
  std::vector<Coordinate> nodes_;
};

#endif  // MODEL_ROAD_H_
