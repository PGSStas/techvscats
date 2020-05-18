#include "particle_handler.h"

std::mt19937 ParticleHandler::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

ParticleHandler::ParticleHandler(const Size& owner_size,
                                 const Coordinate& owner_coordinates,
                                 const int& owner_delta_time)
    : owner_coordinates_(owner_coordinates), owner_size_(owner_size),
      owner_delta_time_(owner_delta_time) {}

void ParticleHandler::Tick() {
  if (event_to_id_[static_cast<int>(Event::kCreate)] != -1) {
    CreateParticleFromId(event_to_id_[static_cast<int>(Event::kCreate)]);
    event_to_id_[static_cast<int>(Event::kCreate)] = -1;
  }
  if (period_ <= 0) {
    return;
  }
  wait_time_ -= owner_delta_time_;
  if (wait_time_ <= 0) {
    wait_time_ += period_;
    Coordinate rand_coordinate = owner_coordinates_;
    rand_coordinate +=
        Size(random_generator_() % (static_cast<int>(owner_size_.width/1.5))
                 - owner_size_.width / 3,
             random_generator_() % (static_cast<int>(owner_size_.height/1.5))
                 - owner_size_.height / 3);

    particle_queue.emplace_back(event_to_id_[static_cast<int>(Event::kLive)],
                                owner_size_, rand_coordinate);
  }
}

void ParticleHandler::SetEvents(const std::vector<int>& event_to_id,
                                int period) {
  event_to_id_ = event_to_id;
  period_ = period;
  wait_time_ = period;
}

void ParticleHandler::SetParticlePacks(const ParticleHandler& other) {
  SetEvents(other.event_to_id_, other.period_);
}

void ParticleHandler::PlayOwnerDeath() {
  if (event_to_id_[static_cast<int>(Event::kDeath)] != -1) {
    CreateParticleFromId(event_to_id_[static_cast<int>(Event::kDeath)]);
  }
}

void ParticleHandler::Clear() {
  particle_queue.clear();
}

const std::list<ParticleParameters>&
ParticleHandler::GetParticlesQueue() const {
  return particle_queue;
}

bool ParticleHandler::IsReadyToCreateParticle() const {
  return !particle_queue.empty();
}

void ParticleHandler::AddParticle(ParticleParameters particle) {
  particle_queue.push_back(particle);
}

void ParticleHandler::CreateParticleFromId(int id) {
  particle_queue.emplace_back(id, owner_size_, owner_coordinates_);
}

void ParticleHandler::SetPeriod(int period) {
  period_ = period;
}
