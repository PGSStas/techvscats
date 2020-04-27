#ifndef GAMEOBJECT_PARTICLE_H_
#define GAMEOBJECT_PARTICLE_H_

#include "GameObject/moving_object.h"
#include "View/animation_player.h"
#include "View/size_handler.h"

class Particle : public GameObject {
 public:
  explicit Particle(Size size = {-1, -1}, int repeat_number = -1);
  Particle(const Particle& other);
  ~Particle() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void SetParameters(Size size, Coordinate position, int repeat_number);
  bool IsDead() const;
 private:
  bool is_dead_ = false;
  int time_to_death_ = 0;
  int repeat_number_ = 0;
};

#endif  // GAMEOBJECT_PARTICLE_H_
