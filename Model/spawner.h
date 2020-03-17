#ifndef SPAWNER_H
#define SPAWNER_H

#include "model.h"

class Spawner {
 public:
  Spawner(int road_num,int wave_num);
  //Enemy SpawnUnit(Enemy*);

 private:

  // Wave current_wave; // Какая волная сейчас выпускается
  int road; // На какой дороге я нахожусь

};

#endif //SPAWNER_H
