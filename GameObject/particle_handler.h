#ifndef GAMEOBJECT_PARTICLE_HANDLER_H_
#define GAMEOBJECT_PARTICLE_HANDLER_H_

#include <chrono>
#include <memory>
#include <random>
#include <list>

#include "Model/coordinate.h"

// To avoid multi include
struct ParticleParameters {
  ParticleParameters(
      int particle_id, Size size, Coordinate position,
      int animation_times = 1, double speed = 0) :
      particle_id(particle_id), size(size), position(position),
      animation_times(animation_times), speed(speed) {}
  int particle_id;
  Size size;
  Coordinate position;
  int animation_times;
  double speed;
};
// Particulars are created when an object is created, when it dies, and
// during its lifetime. The particulars themselves are drawn objects.
class ParticleHandler {
 public:
  ParticleHandler(const Size& carrier_size,
                  const Coordinate& carrier_coordinates,
                  const int& carrier_delta_time);

  void Tick();
  void AddParticle(ParticleParameters particle);
  void SetAtCreationParticlePack(int at_death_id, int at_creation_id = -1);
  void SetAliveParticlePack(int while_alive_id, int period);
  void SetParticlePacks(const ParticleHandler& other);
  void SetPeriod(int period);
  void CarrierDeath();
  void Clear();

  const std::list<ParticleParameters>& GetWaitParticles() const;
  bool IsReadyToCreateParticle() const;

 private:
  void CreateParticleFromId(int id);
  const Coordinate& carrier_coordinates_;
  const Size& carrier_size_;
  const int& carrier_delta_time_;

  std::list<ParticleParameters> wait_particles_;

  int at_death_id_ = -1;
  int at_creation_id_ = -1;

  int while_alive_id_ = -1;
  int period_ = -1;

  int wait_time_ = 0;

  static std::mt19937 random_generator_;
};

#endif  // GAMEOBJECT_PARTICLE_HANDLER_H_
