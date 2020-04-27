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
                  int animation_duration=constants::kTimeScale);

  void Tick(int delta_time);
  void Reset();
  const QImage& GetCurrentFrame() const;
  int GetAnimationDuration() const;
  void Rescale(Size to_size);

 private:
  Size picture_size_ ;
  uint current_frame_ = 0;
  int wait_till_next_frame_ = 0;
  int time_between_frames_ = 0;

  std::shared_ptr<std::vector<QImage>> frames_;
  std::vector<QImage> frames_rescaled_ = {
      QImage("::resources/images/error.png")};
};

#endif  // VIEW_ANIMATION_PLAYER_H_
