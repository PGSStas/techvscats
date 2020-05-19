#ifndef VIEW_ANIMATION_PLAYER_H_
#define VIEW_ANIMATION_PLAYER_H_

#include <vector>
#include <memory>
#include <QPixmap>
#include <QPainter>
#include "Model/coordinate.h"
#include "Model/constants.h"
#include "Model/size.h"
class AnimationPlayer {
 public:
  AnimationPlayer() = default;
  AnimationPlayer(const std::shared_ptr<std::vector<QPixmap>>& frames,
                  int animation_duration = constants::kTimeScale);

  void Tick(int delta_time);
  void Reset();
  const QPixmap& GetCurrentFrame() const;
  int GetAnimationDuration() const;
  void Rescale(Size to_size);

 private:
  Size picture_size_ = {0, 0};
  uint current_frame_ = 0;
  int wait_till_next_frame_ = 0;
  int time_between_frames_ = 0;

  std::shared_ptr<std::vector<QPixmap>> frames_;
  std::vector<QPixmap> frames_rescaled_ =
      {QPixmap("::resources/images/error.png")};
};

#endif  // VIEW_ANIMATION_PLAYER_H_
