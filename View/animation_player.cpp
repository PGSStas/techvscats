#include "animation_player.h"

AnimationPlayer::AnimationPlayer(
    const std::shared_ptr<std::vector<QImage>>& frames,
    double mspf_coefficient, bool cycled) : frames_(frames), cycled_(cycled) {
  time_between_frames_ = mspf_coefficient * constants::kDefaultTimeBetweenFrames;
  frames_rescaled_ = std::make_shared<std::vector<QImage>>(*frames);
}

AnimationPlayer::AnimationPlayer(
    const std::shared_ptr<std::vector<QImage>>& frames, int animation_duration,
    bool cycled) : AnimationPlayer(frames,
        1.0 * animation_duration / frames->size(), cycled) {}

void AnimationPlayer::Tick(int time) {
  if (time - last_frame_change_time_ >= time_between_frames_) {
    if (cycled_ || current_frame_ + 1 != frames_->size()) {
      current_frame_ = (current_frame_ + 1) % frames_->size();
      last_frame_change_time_ = time;
    }
  }
}

const QImage& AnimationPlayer::GetCurrentFrame() const {
  return (*frames_rescaled_)[current_frame_];
}

void AnimationPlayer::SetTimeBetweenFrames(int new_time) {
  time_between_frames_ = new_time;
}

void AnimationPlayer::Reset(int time) {
  current_frame_ = 0;
  last_frame_change_time_ = time;
}

void AnimationPlayer::Rescale(Size to_size) {
  for (int i = 0; i < frames_->size(); i++) {
    (*frames_rescaled_)[i] = (*frames_)[i].scaled(to_size.width,
        to_size.height, Qt::KeepAspectRatio);
  }
}

void AnimationPlayer::SetAnimationDuration(int duration) {
  time_between_frames_ = 1.0 * duration / frames_->size();
}
