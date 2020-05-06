#include "sound_vector.h"

SoundVector::SoundVector(const QString& path, int audio_roads_count) {
  for (int i = 0; i < audio_roads_count; i++) {
    auto sound_effect = std::make_shared<QSoundEffect>();
    sound_effect->setVolume(0.4);
    sound_effect->setSource(QUrl("qrc:resources/" + path));
    sounds_.push_back(std::move(sound_effect));
  }
}

void SoundVector::Play() {
  if (sounds_.empty()) {
    return;
  }
  sounds_[current_sound_++]->play();
  current_sound_ %= sounds_.size();
}
