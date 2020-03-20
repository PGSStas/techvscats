#include "model.h"

void Model::SetGameModel(int level_id) {
  current_round_number_ = 0;
  gold_ = 100;
  score_ = 0;

  switch (level_id) {
    case 0: int x;

      // To be changed. All this is need to be downloaded form file.
      Enemy temporary_enemy;
      EnemyPack temporary_enemy_pack;
      temporary_enemy_pack.enemy = temporary_enemy;
      temporary_enemy_pack.times = 3;

      Wave temporary_wave;
      temporary_wave.frequency = 1000;
      temporary_wave.road_number = 0;
      temporary_wave.enemies = temporary_enemy_pack;

      roads_count_ = 1;
      rounds_count_ = 1;
      time_between_waves_ = 10000;
      rounds_.resize(rounds_count_, std::vector<Wave>(roads_count_));

      rounds_[0][0] = temporary_wave;

      roads_.resize(roads_count_);
      std::vector<Coordinate> nodes = {{0, 0}, {100, 100}};
      Road temporary_road(nodes);
      roads_[0] = temporary_road;
      //
  }

}