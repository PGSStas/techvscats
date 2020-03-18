#ifndef CONTROLLER_SPAWNER_H_
#define CONTROLLER_SPAWNER_H_

#include "Controller/AbstractController.h"
#include "Model/Wave.h"
class Spawner {
 public:
  Spawner(int road_num, int wave_num);
  void SpawnUnit(Enemy*);

 private:
  Wave* current_wave_{};
  int road_;  // На какой дороге я нахожусь
};

#endif  // CONTROLLER_SPAWNER_H_
