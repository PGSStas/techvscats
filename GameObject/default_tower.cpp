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
        if (have_possible_to_shoot_) {
          wait_time_ = 0;
          action = Action::pre_fire;
        }
      }
      break;
    case Action::pre_fire:UpdateAim();
      if (!have_possible_to_shoot_) {
        action = Action::reload;
        wait_time_ = reload_time_;
        return;
      }
      if (wait_time_ > pre_fire_time_) {
        if (have_possible_to_shoot_) {
          DoAction();
          action = Action::post_fire;
          wait_time_ = 0;
        }
        break;
        case Action::post_fire:
          if(wait_time_>post_fire_time_){
            action=Action::reload;
          }
          break;
      }
  }
}

void DefaultTower::UpdateAim() {
  if (enemies_.empty()) {
    have_possible_to_shoot_ = false;
    return;
  }
  if (enemy_aim_ != nullptr && !enemy_aim_->IsDead()) {
    if (enemy_aim_->GetPosition().GetBetween(position_).GetLength()
        < action_range_) {
      have_possible_to_shoot_ = true;
      return;
    }
  }
  enemy_aim_ = enemies_.back();
  for (auto enemy:enemies_) {
    if (enemy_aim_->GetPosition().GetBetween(position_).GetLength()
        > enemy->GetPosition().GetBetween(position_).GetLength()) {
      enemy_aim_ = enemy;
    }
  }
  have_possible_to_shoot_ = false;
}

void DefaultTower::DoAction() {

}
