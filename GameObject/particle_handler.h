#ifndef GAMEOBJECT_PARTICLE_HANDLER_H_
#define GAMEOBJECT_PARTICLE_HANDLER_H_

#include <chrono>
#include <memory>
#include <random>
#include <list>

#include "Model/coordinate.h"

enum class Event {
  kCreate = 0,
  kDeath = 1,
  kLive = 2
};

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

// Particles are created when an object is created, when it dies, and
// during its lifetime. The particulars themselves are drawn objects.
class ParticleHandler {
 public:
  ParticleHandler(const Size& carrier_size,
                  const Coordinate& carrier_coordinates,
                  const int& carrier_delta_time);

  void Tick();
  void AddParticle(ParticleParameters particle);
  void SetEvents(const std::vector<int>& event_to_id, int period);
  void SetParticlePacks(const ParticleHandler& other);
  void SetPeriod(int period);
  void PlayOwnerDeath();
  void Clear();

  const std::list<ParticleParameters>& GetParticlesInQueue() const;
  bool IsReadyToCreateParticle() const;

 private:
  void CreateParticleFromId(int id);
  const Coordinate& carrier_coordinates_;
  const Size& carrier_size_;
  const int& carrier_delta_time_;

  std::list<ParticleParameters> particle_queue;
  std::vector<int> event_to_id_ = {-1, -1, -1};

  int period_ = -1;
  int wait_time_ = 0;

  static std::mt19937 random_generator_;
};

#endif  // GAMEOBJECT_PARTICLE_HANDLER_H_
