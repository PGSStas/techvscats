#include "particle_handler.h"

ParticleHandler::ParticleHandler(const Size& carrier_size,
                                 const Coordinate& carrier_coordinates) :
    carrier_coordinates_(carrier_coordinates), carrier_size_(carrier_size) {
}

void ParticleHandler::Tick(int delta_time) {
  if (period_ <= 0) {
    return;
  }
  wait_time_ -= delta_time;
  if (wait_time_ <= 0) {
    wait_time_ = period_;

  }
}

void ParticleHandler::SetRotation(Size look_direction) {
  look_direction_ = look_direction;
}

void ParticleHandler::SetAtCreationParticlePack(int at_death_id,
                                                int at_creation_id) {

  at_creation_id_ = at_death_id;
  at_creation_id_ = at_creation_id;
}

void ParticleHandler::SetAliveParticlePack(int while_alive_id, int period,
                                           int radius) {
  while_alive_id_ = while_alive_id;
  period_ = period;
  radius_ = radius;
}

void ParticleHandler::RemoveWaiters() {
  wait_particles_.clear();
}

const std::list<ParticleParameters>& ParticleHandler::GetWaitParticles() const {
  return wait_particles_;
}

bool ParticleHandler::IsReadyToCreateParticle() const {
  return !wait_particles_.empty();
}
void ParticleHandler::AddParticle(ParticleParameters particle) {
  wait_particles_.push_back(particle);
}
