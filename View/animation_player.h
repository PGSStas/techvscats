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
      Size size,
      int time_between_frames = constants::kDefaultTimeBetweenFrames,
      bool cycled = true);
  explicit AnimationPlayer(const std::shared_ptr<std::vector<QImage>>& frames,
      int time_between_frames = constants::kDefaultTimeBetweenFrames,
      bool cycled = true);

  void Tick(int time);
  void Reset(int time);
  const QImage& GetCurrentFrame() const;

  void Rescale(Size to_size);
  void SetTimeBetweenFrames(int new_time);

 private:
  int current_frame_ = 0;
  int last_frame_change_time_ = 0;

  std::shared_ptr<std::vector<QImage>> frames_;
  std::shared_ptr<std::vector<QImage>> frames_rescaled_;
  int time_between_frames_ = constants::kDefaultTimeBetweenFrames;
  bool cycled_{};
};

#endif  // VIEW_ANIMATION_PLAYER_H_
