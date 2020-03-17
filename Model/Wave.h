#ifndef WAVE_H_
#define WAVE_H_

#include "vector"

struct Wave { // to be updated
  int frequency;
  int road_num;
  std::vector<std::pair<int, int>> enemyid_times;
};

#endif  // WAVE_H_
