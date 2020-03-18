#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include "AbstractModel.h"
#include "Controller/AbstractController.h"

class Model : public AbstractModel {
 public:
  explicit Model(AbstractController*);
  AbstractController* controller;
  // void SetDataBase(int level_id);
  // Wave GetWave(int wave_id, int road_id);
  // Wave SumWaves(Wave*, Wave*)
  ~Model() override = default;
 private:
  int gold_{};
  int score_{};
};

#endif  // MODEL_MODEL_H_
