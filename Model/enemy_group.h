#ifndef MODEL_ENEMY_GROUP_H_
#define MODEL_ENEMY_GROUP_H_

#include <list>
#include <utility>

#include "GameObject/enemy.h"

struct EnemyGroup {
  EnemyGroup(int spawn_period, int enemy_id, int time_of_next_spawn,
             int group_size, int road_to_spawn)
      : spawn_period(spawn_period), enemy_id(enemy_id),
        time_of_next_spawn(time_of_next_spawn),
        group_size(group_size), road_to_spawn(road_to_spawn) {}

  int spawn_period;
  int enemy_id;
  int time_of_next_spawn;
  int group_size;
  int road_to_spawn;
};

#endif  // MODEL_ENEMY_GROUP_H_
