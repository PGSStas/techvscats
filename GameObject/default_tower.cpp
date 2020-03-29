#include "default_tower.h"
#include "QDebug"
DefaultTower::DefaultTower(const std::list<std::shared_ptr<Enemy>>& enemies) :
    ActiveTower(enemies, 1) {}

DefaultTower::DefaultTower(const std::shared_ptr<Building>& other) :
    ActiveTower(other) {}

void DefaultTower::Tick(int controller_current_time) {
  wait_time_ += controller_current_time - object_current_time_;
  object_current_time_ = controller_current_time;

  switch (action) {
    case Action::reload:
      if (wait_time_ > reload_time_) {
        UpdateAim();
        if (have_possible_to_shoot) {
          wait_time_ = reload_time_;
          action = Action::pre_fire;
        }
      }
      break;
    case Action::pre_fire:UpdateAim();
      if (!have_possible_to_shoot) {
        action = Action::reload;
        return;
      }
      if (wait_time_ > reload_time_ + pre_fire_time_) {
        if (have_possible_to_shoot) {
          DoAction();
          action = Action::post_fire;

        }
        break;
        case Action::post_fire:break;
      }
  }
}
