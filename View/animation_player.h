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
  explicit AnimationPlayer(const std::vector<QImage>& frames, double mspf_ = 1);
  AnimationPlayer(const std::vector<QImage>& frames, int animation_duration);

  void Tick(int time);
  void Reset(int time);
  const QImage& GetCurrentFrame() const;

  void Rescale(Size to_size);

 private:
  int current_frame_ = 0;
  int last_frame_change_time_ = 0;

  const std::vector<QImage>& frames_;
  std::vector<QImage> frames_rescaled_;
  double time_between_frames_;
};

#endif  // VIEW_ANIMATION_PLAYER_H_
