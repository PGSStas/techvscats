#include "music_player.h"
#include <QDebug>

MusicPlayer::MusicPlayer()
    : main_player_(std::make_shared<QMediaPlayer>()),
      main_playlist_(std::make_shared<QMediaPlaylist>(main_player_.get())),
      button_sound_(std::make_shared<QSoundEffect>()),
      game_over_sound_(std::make_shared<QSoundEffect>()),
      game_won_sound_(std::make_shared<QSoundEffect>()),
      sale_sound_(std::make_shared<QSoundEffect>()),
      not_enough_money_sound_(std::make_shared<QSoundEffect>()),
      new_wave_(std::make_shared<QSoundEffect>()) {
  main_player_->setPlaylist(main_playlist_.get());

  main_playlist_->addMedia(QUrl("qrc:resources/sounds/menu_sound.mp3"));
  main_playlist_->addMedia(QUrl("qrc:resources/sounds/game_sound.mp3"));
  main_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

  button_sound_->setSource(QUrl("qrc:resources/sounds/button_click.wav"));
  game_over_sound_->setSource(QUrl("qrc:resources/sounds/game_over_sound.wav"));
  game_won_sound_->setSource(QUrl("qrc:resources/sounds/game_won_sound.wav"));
  sale_sound_->setSource(QUrl("qrc:resources/sounds/sale_sound.wav"));
  not_enough_money_sound_->setSource(QUrl(
      "qrc:resources/sounds/not_enough_money_sound.wav"));
  new_wave_->setSource(QUrl("qrc:resources/sounds/new_wave_sound.wav"));

  SetVolume(100);
  main_player_->play();
}

void MusicPlayer::SetVolume(int volume) {
  if (volume == 0) {
    main_player_->stop();
  } else {
    main_player_->play();
  }
  // Volume in QMediaPlayer is ranging from 0 to 100,
  // and in QSoundEffect from 0 to 1.0
  main_player_->setVolume(volume);
  game_over_sound_->setVolume(volume / 100.);
  button_sound_->setVolume(volume / 100.);
  game_won_sound_->setVolume(volume / 100.);
  sale_sound_->setVolume(volume / 100.);
  not_enough_money_sound_->setVolume(volume / 100.);
  new_wave_->setVolume(0.4 * volume / 100.);
}

void MusicPlayer::StartMenuMusic() {
  main_playlist_->setCurrentIndex(kMenuMusic);
  qDebug() << main_playlist_->currentIndex();
}

void MusicPlayer::StartGameMusic() {
  main_playlist_->setCurrentIndex(kGameMusic);
  qDebug() << main_playlist_->currentIndex();
  main_player_->play();
}

void MusicPlayer::PlayGameOverSound() {
  game_over_sound_->play();
}

void MusicPlayer::PlayButtonSound() {
  button_sound_->play();
}

void MusicPlayer::PlayGameWonSound() {
  game_won_sound_->play();
}

void MusicPlayer::PlayNewWaveSound() {
  new_wave_->play();
}

void MusicPlayer::PlaySaleSound() {
  sale_sound_->play();
}

void MusicPlayer::PlayNotEnoughMoneySound() {
  not_enough_money_sound_->play();
}

