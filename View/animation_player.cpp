#include "animation_player.h"

AnimationPlayer::AnimationPlayer(
    const std::shared_ptr<std::vector<QImage>>& frames, int animation_duration)
    : frames_(frames), frames_rescaled_(*frames) {
  time_between_frames_ = 1.0 * animation_duration / frames->size();
  Reset();
}

void AnimationPlayer::Tick(int delta_time) {
  wait_till_next_frame_ -= delta_time;
  if (wait_till_next_frame_ >= 0) {
    return;
  }
  current_frame_ = (current_frame_ + 1) % frames_->size();
  wait_till_next_frame_ += time_between_frames_;
}
#include <qdebug.h>
const QImage& AnimationPlayer::GetCurrentFrame() const {
  qDebug()<<current_frame_;
  return frames_rescaled_[current_frame_];
}

int AnimationPlayer::GetAnimationDuration() const {
  return frames_->size() * time_between_frames_;
}

void AnimationPlayer::Reset() {
  current_frame_ = 0;
  wait_till_next_frame_ = time_between_frames_;
}

void AnimationPlayer::Rescale(Size to_size) {
  if (frames_ == nullptr || frames_->empty()) {
    return;
  }
  if (std::abs(picture_size_.width - to_size.width)
      + std::abs(picture_size_.height - to_size.height) < 5) {
    return;
  }
  for (uint i = 0; i < frames_->size(); i++) {
    frames_rescaled_[i] =
        (*frames_)[i].scaled(to_size.width + 1, to_size.height + 1,
                             Qt::KeepAspectRatio);
  }
  picture_size_ = to_size;
}
