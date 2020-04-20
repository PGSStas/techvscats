#include "animation_player.h"

AnimationPlayer::AnimationPlayer(const std::shared_ptr<std::vector<QImage>>&
  frames, int time_between_frames, bool cycled) : frames_(frames),
  time_between_frames_(time_between_frames), cycled_(cycled) {
  frames_rescaled_ = std::make_shared<std::vector<QImage>>(*frames);
}

AnimationPlayer::AnimationPlayer(const std::shared_ptr<std::vector<QImage>>&
  frames, Size size, int time_between_frames, bool cycled) :
  AnimationPlayer(frames, time_between_frames, cycled) {
  Rescale(size);
}

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
