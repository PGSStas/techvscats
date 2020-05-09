#include "sound_vector.h"

SoundVector::SoundVector(const QString& path, int audio_roads_count) {
  for (int i = 0; i < audio_roads_count; i++) {
    sounds_.push_back(new QMediaPlayer);
    auto playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:resources/" + path));
    playlist->setCurrentIndex(0);
    sounds_[i]->setVolume(30);
    sounds_[i]->setPlaylist(playlist);
    sounds_[i]->playlist()->setCurrentIndex(0);
    roads_count_++;
  }
}

void SoundVector::Play() {
  if (!roads_count_) {
    return;
  }
  sounds_[current_sound_++]->play();
  current_sound_ %= roads_count_;
}
