#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <algorithm>
#include <memory>
#include <vector>
#include <QPainter>

#include "particle_handler.h"
#include "Model/coordinate.h"
#include "Model/size.h"
#include "View/size_handler.h"
#include "View/animation_player.h"

class GameObject {
 public:
  explicit GameObject(Size size, Coordinate position = {0, 0});
  virtual ~GameObject() = default;

  virtual void Tick(int current_time) = 0;
  void UpdateTime(int current_time);
  virtual void Draw(QPainter* painter,
                    const SizeHandler& size_handler) const = 0;

  void SetAnimationPlayers(
      const std::vector<AnimationPlayer>& animation_players);
  void Rescale(Size to_size);

  void SetPosition(Coordinate position);
  Coordinate GetPosition() const;
  ParticleHandler* GetParticleHandler();
  Size GetSize() const;

 protected:
  std::vector<AnimationPlayer> animation_players_;
  std::vector<int> action_timings_;
  Size size_;
  Coordinate position_;
  ParticleHandler particle_handler_;
  int object_life_time_ = 0;
  int delta_time_ = 0;

 private:
  int object_last_time_ = 0;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
