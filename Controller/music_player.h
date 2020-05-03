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
  void StartMenuMusic();
  void StopMenuMusic();
  void StartGameMusic();
  void StopGameMusic();
  void DeathEnemySound();
  void BoomSound(ProjectileType projectile_type);
  void GameOverSound();
  void ButtonSound();
  void SetVolume(int volume);

 private:
  QMediaPlayer* main_player_;
  QMediaPlaylist* main_playlist_;    // Плейлист

  QSoundEffect* button_sound_;

  QSoundEffect* enemy_death_sound_;

  QSoundEffect* bomb_boom_sound_;
  QSoundEffect* laser_boom_sound_;
  QSoundEffect* aimed_boom_sound_;

  QSoundEffect* game_over_sound_;
};

#endif //MUSIC_PLAYER_H
