#ifndef GAMEOBJECT_PARTICLE_H_
#define GAMEOBJECT_PARTICLE_H_

#include "GameObject/moving_object.h"
#include "View/animation_player.h"
#include "View/size_handler.h"

// The Particles themselves are drawn objects.
class Particle : public GameObject {
 public:
  explicit Particle(Size size = {-1, -1}, int repeat_number = -1);
  Particle(const Particle& other);
  ~Particle() override = default;

  void Tick(int current_time) override;
  void SetSoundId(int id);
  int GetSoundId() const;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void SetIfEmpty(Size size, Coordinate position, int repeat_number);
  bool IsDead() const;

 private:
  bool is_dead_ = false;
  int time_to_death_ = 0;
  int repeat_number_ = 0;
  int sound_id_ = -1;

  // The lifetime of a Particle = the lifetime of the animation.
  // Due to the fact that the partial is removed not on the tick X but on X+1,
  // the animation between them has time to change from the last to the first
  // frame. And there is an instant glare.
  const double kLifetimeOffset = 0.97;
};

#endif  // GAMEOBJECT_PARTICLE_H_
