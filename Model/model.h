#ifndef MODEL_H
#define MODEL_H

#include <Controller/controller.h>

class Controller;

class Model {
 public:
  Model(Controller*);
  ~Model();
  Controller* controller;
  int gold;
  //std::vector <Enemy> id_to_Enemy;
  //std::vector<GameObject*> obj_handler;
  //void SetDataBase(int level_id = 0); // Загружает базу данных в соответствии с текущим уровнем
  //GameMap map;
  //std::vector<std::vector<int>> possible_upgrades;
  //Wave SumWaves(Wave*, Wave*)
 private:

};

#endif // MODEL_H
