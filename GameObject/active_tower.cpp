#include "active_tower.h"

ActiveTower::ActiveTower(const std::list<std::shared_ptr<Enemy>>& enemies,
                         int max_aim_count) :
    Building(enemies, std::vector<std::shared_ptr<Building>>{}, 1) {
  max_aims_ = max_aim_count;
}

ActiveTower::ActiveTower(const std::shared_ptr<const Building>& other) :
    Building(other) {}

void ActiveTower::Tick(int controller_current_time) {
  wait_time_ += (controller_current_time - object_current_time_)
      * action_time_coefficient_;
  object_current_time_ = controller_current_time;

  switch (action) {
    case Action::reload:
      if (wait_time_ > reload_time_) {
        UpdateAim();
        if (have_possible_to_action_) {
          wait_time_ = 0;
          action = Action::pre_fire;
        }
      }
      break;
    case Action::pre_fire:UpdateAim();
      if (!have_possible_to_action_) {
        action = Action::reload;
        wait_time_ = reload_time_;
        return;
      }
      if (wait_time_ > pre_fire_time_) {
        if (have_possible_to_action_) {
          DoAction();
          action = Action::post_fire;
          wait_time_ = 0;
        }
        break;
        case Action::post_fire:
          if (wait_time_ > post_fire_time_) {
            action = Action::reload;
          }
        break;
      }
  }
}
#include "qdebug.h"
void ActiveTower::UpdateAim() {

  if (enemies_.size() == 0) {
    have_possible_to_action_ = false;
    aims_.clear();
    return;
  }
  aims_.remove_if([&](const auto& object) {
    return (object->IsDead() ||
        object->GetPosition().GetBetween(position_).GetLength()
            > action_range_);
  });

  if (static_cast<int>(aims_.size()) == max_aims_) {
    have_possible_to_action_ = true;
    return;
  }

  for (auto& enemy:enemies_) {
    if (static_cast<int>(aims_.size()) == max_aims_
        || aims_.size() == enemies_.size()) {
      break;
    }
    bool can_add = true;
    std::shared_ptr<GameObject> new_aim = enemy;
    if (new_aim->GetPosition().GetBetween(position_).GetLength()
        > action_range_) {
      continue;
    }
    for (auto& aim:aims_) {
      if (aim->GetPosition() == enemy->GetPosition()) {
        can_add = false;
        break;
      }
    }
    if (can_add) {
      aims_.push_back(new_aim);
    }
  }
  have_possible_to_action_ = !aims_.empty();
}

void ActiveTower::DoAction() {
  is_ready_to_create_projectile_ = true;
}
