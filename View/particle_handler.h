#ifndef VIEW_PARTICLE_HANDLER_H_
#define VIEW_PARTICLE_HANDLER_H_

#include "Model/coordinate.h"

class ParticleHandler {
 public:
  void Tick(int current_time_delta);
  void SetArea(double area);
  void SetPeriod(int time);



 private:

  double area = 0;
  Coordinate* carrier_coordinate_ = nullptr;

  int wait_time = 0;

};

#endif  // VIEW_PARTICLE_HANDLER_H
