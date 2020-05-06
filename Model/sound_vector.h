#ifndef MODEL_SOUND_VECTOR_H_
#define MODEL_SOUND_VECTOR_H_

#include <QSoundEffect>

#include <memory>
#include <vector>
#include <utility>

class SoundVector {
 public:
  explicit SoundVector(const QString& path, int audio_roads_count);
  void Play();

 private:
  std::vector<std::shared_ptr<QSoundEffect>> sounds_;
  int current_sound_ = 0;
};

#endif  // MODEL_SOUND_VECTOR_H_
