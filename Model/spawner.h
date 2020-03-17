#ifndef SPAWNER_H
#define SPAWNER_H

#include "model.h"

class Spawner {
  Spawner(int road_num,int wave_num);
 public:
  int road; // На какой дороге я нахожусь
  //Enemy SpawnUnit(Enemy*);
  // Wave current_wave; // Какая волная сейчас выпускается

 private:

};

#endif //SPAWNER_H
