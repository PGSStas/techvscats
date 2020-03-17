#ifndef WAVE_H
#define WAVE_H

#include "vector"

struct Wave { // to be updated
  int frequency;
  int road_num;
  std::vector<std::pair<int, int>> enemyid_times;
};

#endif //WAVE_H
