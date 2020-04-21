#include "animation_player.h"

AnimationPlayer::AnimationPlayer(const std::vector<QImage>& frames,
                                 double mspf_) : AnimationPlayer(
    frames,
    static_cast<int>( frames.size() * mspf_ * constants::kTimeScale)) {}

AnimationPlayer::AnimationPlayer(
    const std::vector<QImage>& frames, int animation_duration)
    : frames_(frames) {
  frames_rescaled_ = frames;
  time_between_frames_ = 1.0 * animation_duration / frames.size();
}

void AnimationPlayer::Tick(int time) {
  if (time - last_frame_change_time_ >= time_between_frames_) {
    if (current_frame_ + 1 != frames_.size()) {
      current_frame_ = (current_frame_ + 1) % frames_.size();
      last_frame_change_time_ = time;
    }
  }
}

const QImage& AnimationPlayer::GetCurrentFrame() const {
  return frames_rescaled_[current_frame_];
}

void AnimationPlayer::Reset(int time) {
  current_frame_ = 0;
  last_frame_change_time_ = time;
}

void AnimationPlayer::Rescale(Size to_size) {
  for (int i = 0; i < frames_.size(); i++) {
    frames_rescaled_[i] = frames_[i].scaled(to_size.width,
                                            to_size.height,
                                            Qt::KeepAspectRatio);
  }
}
