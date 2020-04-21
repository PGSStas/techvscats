#ifndef GAMEOBJECT_PARTICLE_H_
#define GAMEOBJECT_PARTICLE_H_

#include "GameObject/moving_object.h"
#include "View/animation_player.h"
#include "View/size_handler.h"

class Particle : public MovingObject {
 public:
  Particle(int life_time, AnimationPlayer animation_player,
           Size size = {-1, -1}, Coordinate position = {-1, -1},
           Size look_direction = {-1, -1}, double speed = 0);
  ~Particle() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void Move() override;
 private:
  Size look_direction_;
  int life_time_;
  AnimationPlayer animation_player_;
};

#endif  // GAMEOBJECT_PARTICLE_H_
