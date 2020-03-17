#ifndef SPAWNER_H_
#define SPAWNER_H_

#include "Model/AbstractModel.h"

class Spawner {
 public:
  Spawner(int road_num, int wave_num);
  void SpawnUnit(Enemy*);

 private:
  Wave current_wave;
  int road;  // На какой дороге я нахожусь
};

#endif  // SPAWNER_H_
