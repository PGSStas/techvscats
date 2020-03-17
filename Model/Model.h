#ifndef MODEL_H
#define MODEL_H

#include "AbstractModel.h"
#include "Controller/AbstractController.h"

class Model : public AbstractModel {
 public:
  explicit Model(AbstractController*);
  AbstractController* controller;
  //void SetDataBase(int level_id);
  // Wave GetWave(int wave_id, int road_id);
  //Wave SumWaves(Wave*, Wave*)
  ~Model() override = default;
 private:
  int gold{};
  int score{};
};

#endif // MODEL_H
