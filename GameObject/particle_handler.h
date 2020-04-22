#ifndef GAMEOBJECT_PARTICLE_HANDLER_H_
#define GAMEOBJECT_PARTICLE_HANDLER_H_

#include <memory>
#include <list>

#include "Model/coordinate.h"

// To avoid multi include
struct ParticleParameters {
  ParticleParameters(
      int particle_id, Coordinate position,
      Size look_direction, double speed = 0
  ) :
      particle_id(particle_id), position(position),
      look_direction(look_direction), speed(speed) {}
  int particle_id;
  Coordinate position;
  Size look_direction;
  double speed;
};

class ParticleHandler {
 public:
  ParticleHandler(const Size& carrier_size,
                  const Coordinate& carrier_coordinates);

  void Tick(int delta_time);
  void AddParticle(ParticleParameters particle);
  void SetRotation(Size lool_direction);
  void SetAtCreationParticlePack(int at_death_id, int at_creation_id = -1);
  void SetAliveParticlePack(int while_alive_id, int period, int radius);
  void SetParticlePacks(const ParticleHandler& other);
  void Clear();

  const std::list<ParticleParameters>& GetWaitParticles() const;
  bool IsReadyToCreateParticle() const;

 private:
  void CreateProjectileFromMe();
  const Coordinate& carrier_coordinates_;
  const Size& carrier_size_;
  Size look_direction_ = {0, 1};

  std::list<ParticleParameters> wait_particles_;

  int at_death_id_ = -1;
  int at_creation_id_ = -1;

  int while_alive_id_ = -1;
  int period_ = -1;
  int radius_ = -1;

  int wait_time_ = 0;
};

#endif  // GAMEOBJECT_PARTICLE_HANDLER_H
