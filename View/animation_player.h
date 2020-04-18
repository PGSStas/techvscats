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
  AnimationPlayer(const std::shared_ptr<std::vector<QImage>>& frames,
      int time_between_frames);

  const QImage& GetNextFrame(int time);
  const QImage& GetCurrentFrame() const;

  void SetTimeBetweenFrames(int new_time);

 private:
  int current_frame_ = 0;
  int last_frame_change_time_ = 0;

  std::shared_ptr<std::vector<QImage>> frames_;
  int time_between_frames_ = constants::kDefaultTimeBetweenFrames;
};

#endif  // VIEW_ANIMATION_PLAYER_H_
