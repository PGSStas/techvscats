#include "particle_handler.h"

std::mt19937 ParticleHandler::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

ParticleHandler::ParticleHandler(const Size& carrier_size,
                                 const Coordinate& carrier_coordinates,
                                 const int& carrier_delta_time)
    : carrier_coordinates_(carrier_coordinates), carrier_size_(carrier_size),
      carrier_delta_time_(carrier_delta_time) {}

void ParticleHandler::Tick() {
  if (is_at_creation_not_used_) {
    CreateParticleFromId(at_creation_id_);
    is_at_creation_not_used_ = false;
  }

  if (period_ <= 0) {
    return;
  }
  wait_time_ -= carrier_delta_time_;
  if (wait_time_ <= 0) {
    wait_time_ += period_;
    Coordinate rand_coordinate = carrier_coordinates_;
    rand_coordinate +=
        Size(random_generator_() % (static_cast<int>(carrier_size_.height))
                 - carrier_size_.height / 2,
             random_generator_() % (static_cast<int>(carrier_size_.width))
                 - carrier_size_.width / 2);

    particle_queue.emplace_back(while_alive_id_, carrier_size_,
                                rand_coordinate);
  }
}

void ParticleHandler::SetAtCreationParticlePack(int at_death_id,
                                                int at_creation_id) {
  at_death_id_ = at_death_id;
  at_creation_id_ = at_creation_id;
  if (at_creation_id != -1) {
    is_at_creation_not_used_ = true;
  }
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

void ParticleHandler::PlayOwnerDeath() {
  if (at_death_id_ != -1) {
    CreateParticleFromId(at_death_id_);
    at_death_id_ = -1;
  }
}

void ParticleHandler::Clear() {
  particle_queue.clear();
}

const std::list<ParticleParameters>& ParticleHandler::GetWaitingParticles() const {
  return particle_queue;
}

bool ParticleHandler::IsReadyToCreateParticle() const {
  return !particle_queue.empty();
}

void ParticleHandler::AddParticle(ParticleParameters particle) {
  particle_queue.push_back(particle);
}

void ParticleHandler::CreateParticleFromId(int id) {
  particle_queue.emplace_back(id, carrier_size_, carrier_coordinates_);
}

void ParticleHandler::SetPeriod(int period) {
  period_ = period;
}
