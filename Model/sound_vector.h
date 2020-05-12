#ifndef MODEL_SOUND_VECTOR_H_
#define MODEL_SOUND_VECTOR_H_

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <memory>
#include <vector>
#include <utility>

class SoundVector {
 public:
  explicit SoundVector(const QString& path, int audio_roads_count);
  void Play();
  void Stop();
  void SetVolume(int volume);

 private:
  int roads_count_ = 0;
  std::vector<std::shared_ptr<QMediaPlayer>> sounds_;
  std::vector<std::shared_ptr<QMediaPlaylist>> playlists_;
  int current_sound_ = 0;
};

#endif  // MODEL_SOUND_VECTOR_H_
