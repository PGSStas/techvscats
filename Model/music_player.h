#ifndef  MODEL_MUSIC_PLAYER_H_
#define  MODEL_MUSIC_PLAYER_H_

#include <QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QSoundEffect>
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
  QMediaPlayer* main_player_;
  QMediaPlaylist* main_playlist_;

  QSoundEffect* button_sound_;

  QSoundEffect* game_over_sound_;
  QSoundEffect* game_won_sound_;

  QSoundEffect* sale_sound_;
  QSoundEffect* not_enough_money_sound_;

  QSoundEffect* new_wave_;
};

#endif  // MODEL_MUSIC_PLAYER_H_
