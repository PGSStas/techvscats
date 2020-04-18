#include "animation_player.h"

AnimationPlayer::AnimationPlayer
  (const std::shared_ptr<std::vector<QImage>>& frames, int time_between_frames)
  : frames_(frames), time_between_frames_(time_between_frames) {}

const QImage& AnimationPlayer::GetNextFrame(int time) {
  if (time - last_frame_change_time_ >= time_between_frames_) {
    current_frame_ = (current_frame_ + 1) % frames_->size();
    last_frame_change_time_ = time;
  }
  return (*frames_)[current_frame_];
}

AnimationPlayer::AnimationPlayer(const AnimationPlayer& other) :
  frames_(other.frames_), time_between_frames_(other.time_between_frames_) {}

AnimationPlayer& AnimationPlayer::operator=(const AnimationPlayer& other) {
  if (&other == this) {
    return *this;
  }
  frames_ = other.frames_;
  time_between_frames_ = other.time_between_frames_;
  return *this;
}

const QImage& AnimationPlayer::GetCurrentFrame() const {
  return (*frames_)[current_frame_];
}

void AnimationPlayer::SetTimeBetweenFrames(int new_time) {
  time_between_frames_ = new_time;
}
