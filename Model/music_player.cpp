#include "music_player.h"

MusicPlayer::MusicPlayer()
    : main_player_(std::make_shared<QMediaPlayer>()),
      main_playlist_(std::make_shared<QMediaPlaylist>(main_player_.get())),
      button_sound_(std::make_shared<QMediaPlayer>()),
      game_over_sound_(std::make_shared<QMediaPlayer>()),
      game_won_sound_(std::make_shared<QMediaPlayer>()),
      sale_sound_(std::make_shared<QMediaPlayer>()),
      not_enough_money_sound_(std::make_shared<QMediaPlayer>()),
      new_wave_(std::make_shared<QMediaPlayer>()) {
  main_player_->setPlaylist(main_playlist_.get());

  main_playlist_->addMedia(QUrl("qrc:resources/sounds/menu_sound.mp3"));
  main_playlist_->addMedia(QUrl("qrc:resources/sounds/game_sound.mp3"));
  main_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

  SetSound(button_sound_.get(), "qrc:resources/sounds/button_click.mp3");
  SetSound(game_over_sound_.get(), "qrc:resources/sounds/game_over_sound.mp3");
  SetSound(game_won_sound_.get(), "qrc:resources/sounds/game_won_sound.mp3");
  SetSound(sale_sound_.get(), "qrc:resources/sounds/sale_sound.mp3");
  SetSound(not_enough_money_sound_.get(),
           "qrc:resources/sounds/not_enough_money_sound.mp3");
  SetSound(new_wave_.get(), "qrc:resources/sounds/new_wave_sound.mp3");

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
  game_over_sound_->setVolume(volume);
  button_sound_->setVolume(volume);
  game_won_sound_->setVolume(volume);
  sale_sound_->setVolume(volume);
  not_enough_money_sound_->setVolume(volume);
  new_wave_->setVolume(0.4 * volume);
}

void MusicPlayer::StartMenuMusic() {
  main_playlist_->setCurrentIndex(kMenuMusic);
}

void MusicPlayer::StartGameMusic() {
  main_playlist_->setCurrentIndex(kGameMusic);
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

void MusicPlayer::SetSound(QMediaPlayer* player, const QString& path) {
  auto playlist = new QMediaPlaylist;
  playlist->addMedia(QUrl(path));
  playlist->setCurrentIndex(0);

  player->setPlaylist(playlist);
  player->playlist()->setCurrentIndex(0);

}

