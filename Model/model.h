#ifndef MODEL_H
#define MODEL_H

#include "Controller/controller.h"
#include "spawner.h"
#include "road.h"

class Controller;
class Spawner;
class Enemy;
class Road;
class GameObject;

struct Wave { // to be updated
  int frequency;
  int road_num;
  std::vector<std::pair<int, int>> enemyid_times;
};

struct Map {
  std::vector<std::vector<Wave> > Rounds;
  //vector<Road*> roads
  //vector<Building*> buildings;
  //vector<Spawner*> spawners;
  std::vector<GameObject*> obj_handler;
};

class Model {
 public:
  Model(Controller*);
  Controller* controller;
  Map map;

  //void SetDataBase(int level_id = 0);
  //Wave GetWave(int wave_id, int road_id);

  ~Model();

  int gold;
  int score;
  std::vector<Enemy> id_to_Enemy;
//  std::vector <Building> id_to_Building;
  //std::vector<std::vector<int>> possible_upgrades;
  //Wave SumWaves(Wave*, Wave*)

 private:

};

#endif // MODEL_H
