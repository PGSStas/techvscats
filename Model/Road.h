#ifndef MODEL_ROAD_H_
#define MODEL_ROAD_H_

#include <vector>
#include <utility>

class Road {
 public:
  std::pair<double, double> GetNextNode(int direction_num);
 private:
  std::vector<std::pair<double, double>> direction_points_;
};

#endif  // MODEL_ROAD_H_
