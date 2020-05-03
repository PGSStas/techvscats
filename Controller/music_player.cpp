#include "music_player.h"
#include <QDebug>

MusicPlayer::MusicPlayer() {
  main_player_ = new QMediaPlayer();          // Инициализация плеера
  main_playlist_ = new QMediaPlaylist(main_player_);  // Инициализация плейлиста
  main_player_->setPlaylist(main_playlist_);          // Установка плейлиста в аудио плеер

  main_playlist_->addMedia(QUrl("qrc:resources/sounds/menu_sound.mp3"));
  main_playlist_->addMedia(QUrl("qrc:resources/sounds/game_sound.mp3"));
  main_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop); // Зацикливание трека


  button_sound_ = new QSoundEffect();
  button_sound_->setSource(QUrl("qrc:resources/sounds/button_click.wav"));

  enemy_death_sound_ = new QSoundEffect();
  enemy_death_sound_->setSource(QUrl(
      "qrc:resources/sounds/enemy_death_sound.wav"));

  bomb_boom_sound_ = new QSoundEffect();
  bomb_boom_sound_->setSource(QUrl("qrc:resources/sounds/main_boom_sound.wav"));
  laser_boom_sound_ = new QSoundEffect();
  laser_boom_sound_->setSource(QUrl("qrc:resources/sounds/laser_boom_sound.wav"));
  aimed_boom_sound_ = new QSoundEffect();
  aimed_boom_sound_->setSource(QUrl("qrc:resources/sounds/aimed_boom_sound.wav"));

  game_over_sound_ = new QSoundEffect();
  game_over_sound_->setSource(QUrl("qrc:resources/sounds/game_over_sound.wav"));

  main_player_->play();
  SetVolume(100);
}

void MusicPlayer::StartMenuMusic() {
  main_playlist_->setCurrentIndex(0);
  qDebug() << main_playlist_->currentIndex();
}

void MusicPlayer::DeathEnemySound() {
  enemy_death_sound_->play();
}

void MusicPlayer::GameOverSound() {
  game_over_sound_->play();
}

void MusicPlayer::StopMenuMusic() {
  main_player_->stop();
}

void MusicPlayer::StartGameMusic() {
  main_playlist_->setCurrentIndex(1);
  qDebug() << main_playlist_->currentIndex();
  main_player_->play();
}

void MusicPlayer::StopGameMusic() {
  main_player_->stop();
}

void MusicPlayer::ButtonSound() {
  button_sound_->play();
}

void MusicPlayer::SetVolume(int volume) {
  if (volume == 0) {
    main_player_->stop();
  } else {
    main_player_->play();
  }
  main_player_->setVolume(volume);
  enemy_death_sound_->setVolume(volume);
  bomb_boom_sound_->setVolume(volume);
  laser_boom_sound_->setVolume(volume * 0.1);
  aimed_boom_sound_->setVolume(volume);
  game_over_sound_->setVolume(volume);
  button_sound_->setVolume(volume);
}

void MusicPlayer::BoomSound(ProjectileType projectile_type) {
  switch (projectile_type) {
    case ProjectileType::kLaserProjectile:
      laser_boom_sound_->play();
      break;
    case ProjectileType::kBombProjectile:
      bomb_boom_sound_->play();
      break;
    case ProjectileType::kAimedProjectile:
      aimed_boom_sound_->play();
      break;
  }
}
