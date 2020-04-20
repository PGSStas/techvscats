#ifndef VIEW_PARTICLE_H_
#define VIEW_PARTICLE_H_

#include "animation_player.h"
#include "size_handler.h"

class Particle {
 public:
  void Tick(int current_time);
  void Draw(QPainter* painter, const SizeHandler& size_handler) const;

 private:
};

#endif  // VIEW_PARTICLE_H_
