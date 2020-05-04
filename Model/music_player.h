#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <QtMultimedia/QSoundEffect>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include "GameObject/abstract_projectile.h"
#include <QMainWindow>

class MusicPlayer : public QObject {
 public:
  MusicPlayer();
  void SetVolume(int volume);

  void StartMenuMusic();
  void StartGameMusic();
  void ButtonSound();
  void GameOverSound();
  void GameWonSound();
  void NewWaveSound();
  void SaleSound();
  void NotEnoughMoneySound();

 private:
  QMediaPlayer* main_player_;
  QMediaPlaylist* main_playlist_;    // Плейлист

  QSoundEffect* button_sound_;

  QSoundEffect* game_over_sound_;
  QSoundEffect* game_won_sound_;

  QSoundEffect* sale_sound_;
  QSoundEffect* not_enough_money_sound_;

  QSoundEffect* new_wave_;
};

#endif //MUSIC_PLAYER_H
