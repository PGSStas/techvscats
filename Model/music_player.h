#ifndef  MODEL_MUSIC_PLAYER_H_
#define  MODEL_MUSIC_PLAYER_H_

#include <QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <memory>
#include <vector>
#include <utility>
#include "GameObject/abstract_projectile.h"

enum MainMusic {
  kMenuMusic,
  kGameMusic,
  kTitlesMusic
};

class MusicPlayer {
 public:
  MusicPlayer();
  ~MusicPlayer();
  void SetVolume(int volume);

  void StartMenuMusic();
  void StartGameMusic();
  void StartTitlesMusic();
  void PlayButtonSound();
  void PlayGameOverSound();
  void PlayGameWonSound();
  void PlayNewLevelSound();
  void StopNewLevelSound();
  void PlaySaleSound();
  void PlayNotEnoughMoneySound();

  void Pause();
  void Resume();

 private:
  void SetSound(QMediaPlayer* player, const QString& path);
  std::shared_ptr<QMediaPlayer> main_player_;
  std::shared_ptr<QMediaPlaylist> main_playlist_;

  std::shared_ptr<QMediaPlayer> button_sound_;
  std::shared_ptr<QMediaPlayer> game_over_sound_;
  std::shared_ptr<QMediaPlayer> game_won_sound_;
  std::shared_ptr<QMediaPlayer> sale_sound_;
  std::shared_ptr<QMediaPlayer> not_enough_money_sound_;
  std::shared_ptr<QMediaPlayer> new_level_sound_;
  std::vector<std::shared_ptr<QMediaPlaylist>> playlists_;
};

#endif  // MODEL_MUSIC_PLAYER_H_
