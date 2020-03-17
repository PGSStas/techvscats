#ifndef MODEL_WAVE_H_
#define MODEL_WAVE_H_

#include <vector>
#include <utility>

struct Wave {  // to be updated
  int frequency;
  int road_num;
  std::vector<std::pair<int, int>> enemyid_times;
};

#endif  // MODEL_WAVE_H_
