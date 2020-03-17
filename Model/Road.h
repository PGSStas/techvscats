#ifndef ROAD_H
#define ROAD_H
#include <vector>
class Road {
 public:
  std::vector<std::pair<double, double> > direction_points;
  std::pair<double, double> GetNextNode(int direction_num);
};

#endif //ROAD_H
