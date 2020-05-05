#ifndef  MODEL_MUSIC_PLAYER_H_
#define  MODEL_MUSIC_PLAYER_H_

#include <QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <memory>
#include "GameObject/abstract_projectile.h"

enum MainMusic {
  kMenuMusic,
  kGameMusic
};

class MusicPlayer {
 public:
  MusicPlayer();
  void SetVolume(int volume);

  void StartMenuMusic();
  void StartGameMusic();
  void PlayButtonSound();
  void PlayGameOverSound();
  void PlayGameWonSound();
  void PlayNewWaveSound();
  void PlaySaleSound();
  void PlayNotEnoughMoneySound();

 private:
  std::shared_ptr<QMediaPlayer> main_player_;
  std::shared_ptr<QMediaPlaylist> main_playlist_;

  std::shared_ptr<QSoundEffect> button_sound_;
  std::shared_ptr<QSoundEffect> game_over_sound_;
  std::shared_ptr<QSoundEffect> game_won_sound_;
  std::shared_ptr<QSoundEffect> sale_sound_;
  std::shared_ptr<QSoundEffect> not_enough_money_sound_;
  std::shared_ptr<QSoundEffect> new_wave_;
};

#endif  // MODEL_MUSIC_PLAYER_H_
