#ifndef MODEL_ROAD_H_
#define MODEL_ROAD_H_

#include <vector>
#include <utility>

class Road {
 public:
  std::vector<std::pair<double, double> > direction_points;
  std::pair<double, double> GetNextNode(int direction_num);
};

#endif  // MODEL_ROAD_H_
