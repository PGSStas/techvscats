#ifndef VIEW_ANIMATION_PLAYER_H_
#define VIEW_ANIMATION_PLAYER_H_

#include <vector>
#include <memory>
#include <QImage>
#include <QPainter>
#include "Model/coordinate.h"
#include "Model/constants.h"
#include "Model/size.h"

class AnimationPlayer {
 public:
  AnimationPlayer() = default;
  explicit AnimationPlayer(const std::shared_ptr<std::vector<QImage>>& frames,
                           double mspf_ = 1);
  AnimationPlayer(const std::shared_ptr<std::vector<QImage>>& frames,
                  int animation_duration);

  void Tick(int delta_time);
  void Reset();
  const QImage& GetCurrentFrame() const;
  int GetAnimationDuration() const;

  void Rescale(Size to_size);

 private:
  uint current_frame_ = 0;
  int wait_till_next_frame_ = 0;

  std::shared_ptr<std::vector<QImage>> frames_;
  std::vector<QImage> frames_rescaled_;
  int time_between_frames_;
};

#endif  // VIEW_ANIMATION_PLAYER_H_
