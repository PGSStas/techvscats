#ifndef ABSTRACTMODEL_H
#define ABSTRACTMODEL_H

#include "vector"
#include "Controller/Enemy.h"
#include "Wave.h"
#include "Road.h"

struct Map {
  std::vector<GameObject*> obj_handler;
  std::vector<std::vector<Wave> > Rounds;
  std::vector<Road*> roads;
  //vector<Building*> buildings;
  std::vector<Enemy*> enemies;
};

class AbstractModel {
 public:
  virtual ~AbstractModel() = default;
  //virtual void SetDataBase(int level_id) = 0;
  //virtual Wave GetWave(int wave_id, int road_id) = 0;
  Map map;
  //std::vector<Enemy> id_to_Enemy;
  //std::vector <Building> id_to_Building;
  //std::vector<std::vector<int>> possible_upgrades;

};

#endif //ABSTRACTMODEL_H
