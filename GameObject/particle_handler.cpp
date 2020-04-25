#include <QtCore/QtGlobal>
#include "particle_handler.h"

ParticleHandler::ParticleHandler(const Size& carrier_size,
                                 const Coordinate& carrier_coordinates,
                                 const int& carrier_delta_time) :
    carrier_coordinates_(carrier_coordinates), carrier_size_(carrier_size),
    carrier_delta_time_(carrier_delta_time) {}

void ParticleHandler::Tick() {
  if (at_creation_id_ != -1) {
    CreateParticleFromMe(at_creation_id_);
    at_creation_id_ = -1;
  }

  if (period_ <= 0) {
    return;
  }
  wait_time_ -= carrier_delta_time_;
  if (wait_time_ <= 0) {
    wait_time_ = period_;
    Coordinate rand_coordinate = carrier_coordinates_;
    rand_coordinate +=
        Size(qrand() % (static_cast<int>( carrier_size_.height ))
                 - carrier_size_.height / 2,
             qrand() % (static_cast<int>(carrier_size_.width ))
                 - carrier_size_.width / 2);

    wait_particles_.emplace_back(while_alive_id_, carrier_size_,
                                 rand_coordinate, look_direction_);
  }
}

void ParticleHandler::SetRotation(Size look_direction) {
  look_direction_ = look_direction;
}

void ParticleHandler::SetAtCreationParticlePack(int at_death_id,
                                                int at_creation_id) {

  at_death_id_ = at_death_id;
  at_creation_id_ = at_creation_id;
}

void ParticleHandler::SetAliveParticlePack(int while_alive_id, int period) {
  while_alive_id_ = while_alive_id;
  period_ = period;
  wait_time_ = period;
}

void ParticleHandler::SetParticlePacks(const ParticleHandler& other) {
  SetAtCreationParticlePack(other.at_death_id_, other.at_creation_id_);
  SetAliveParticlePack(other.while_alive_id_, other.period_);
}

void ParticleHandler::CarrierDeath() {
  if (at_death_id_ != -1) {
    CreateParticleFromMe(at_death_id_);
    at_death_id_ = -1;
  }
}

void ParticleHandler::Clear() {
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

void ParticleHandler::CreateParticleFromMe(int id) {
  wait_particles_.emplace_back(id, carrier_size_, carrier_coordinates_,
                               look_direction_);
}

void ParticleHandler::SetPeriod(int period) {
  period_ = period;
}
