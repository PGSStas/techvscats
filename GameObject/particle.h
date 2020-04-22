#ifndef GAMEOBJECT_PARTICLE_H_
#define GAMEOBJECT_PARTICLE_H_

#include "GameObject/moving_object.h"
#include "View/animation_player.h"
#include "View/size_handler.h"

class Particle : public MovingObject {
 public:
  Particle(Size size= {-1,-1}, int repeat_number = -1, double speed = 0,
           Size look_direction = {-1, -1});
  Particle(const Particle& other);
  ~Particle() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void SetParameters(Size size, Coordinate position, int repeat_number,
                     Size look_direction, double speed);
  void Move() override;

 private:
  int time_to_death_;
  Size look_direction_;
  int repeat_number_;
};

#endif  // GAMEOBJECT_PARTICLE_H_
