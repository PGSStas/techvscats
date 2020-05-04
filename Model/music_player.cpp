#include "music_player.h"
#include <QDebug>

MusicPlayer::MusicPlayer() {
  main_player_ = new QMediaPlayer();
  main_playlist_ = new QMediaPlaylist(main_player_);
  main_player_->setPlaylist(main_playlist_);

  main_playlist_->addMedia(QUrl("qrc:resources/sounds/menu_sound.mp3"));
  main_playlist_->addMedia(QUrl("qrc:resources/sounds/game_sound.mp3"));
  main_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

  button_sound_ = new QSoundEffect();
  button_sound_->setSource(QUrl("qrc:resources/sounds/button_click.wav"));

  game_over_sound_ = new QSoundEffect();
  game_over_sound_->setSource(QUrl("qrc:resources/sounds/game_over_sound.wav"));

  game_won_sound_ = new QSoundEffect();
  game_won_sound_->setSource(QUrl("qrc:resources/sounds/game_won_sound.wav"));

  sale_sound_ = new QSoundEffect();
  sale_sound_->setSource(QUrl("qrc:resources/sounds/sale_sound.wav"));
  not_enough_money_sound_ = new QSoundEffect();
  not_enough_money_sound_->setSource(QUrl(
      "qrc:resources/sounds/not_enough_money_sound.wav"));

  new_wave_ = new QSoundEffect();
  new_wave_->setSource(QUrl("qrc:resources/sounds/new_wave_sound.wav"));

  main_player_->play();
  SetVolume(100);
}

void MusicPlayer::SetVolume(int volume) {
  if (volume == 0) {
    main_player_->stop();
  } else {
    main_player_->play();
  }
  main_player_->setVolume(volume);
  game_over_sound_->setVolume(volume / 100.);
  button_sound_->setVolume(volume / 100.);
  game_won_sound_->setVolume(volume / 100.);
  sale_sound_->setVolume(volume / 100.);
  not_enough_money_sound_->setVolume(volume / 100.);
  new_wave_->setVolume(0.4 * volume / 100.);
}

void MusicPlayer::StartMenuMusic() {
  main_playlist_->setCurrentIndex(0);
  qDebug() << main_playlist_->currentIndex();
}

void MusicPlayer::StartGameMusic() {
  main_playlist_->setCurrentIndex(1);
  qDebug() << main_playlist_->currentIndex();
  main_player_->play();
}

void MusicPlayer::GameOverSound() {
  game_over_sound_->play();
}

void MusicPlayer::ButtonSound() {
  button_sound_->play();
}

void MusicPlayer::GameWonSound() {
  game_won_sound_->play();
}

void MusicPlayer::NewWaveSound() {
  new_wave_->play();
}

void MusicPlayer::SaleSound() {
  sale_sound_->play();
}

void MusicPlayer::NotEnoughMoneySound() {
  not_enough_money_sound_->play();
}

