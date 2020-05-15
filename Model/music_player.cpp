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
  current_state_ = CurrentState::kPlay;
}

void MusicPlayer::SetVolume(int volume) {
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
  auto playlist = std::make_shared<QMediaPlaylist>();
  playlist->addMedia(QUrl(path));
  playlist->setCurrentIndex(0);

  player->setPlaylist(playlist.get());
  player->playlist()->setCurrentIndex(0);
  playlists_.push_back(std::move(playlist));
}

MusicPlayer::~MusicPlayer() {
  main_player_->stop();
  button_sound_->stop();
  game_over_sound_->stop();
  game_won_sound_->stop();
  sale_sound_->stop();
  not_enough_money_sound_->stop();
  new_wave_->stop();
}

void MusicPlayer::Pause() {
  current_state_ = CurrentState::kPause;
  if (main_player_->state() == QMediaPlayer::PlayingState) {
    main_player_->pause();
  }
  if (game_over_sound_->state() == QMediaPlayer::PlayingState) {
    game_over_sound_->pause();
  }
  if (button_sound_->state() == QMediaPlayer::PlayingState) {
    button_sound_->pause();
  }
  if (game_won_sound_->state() == QMediaPlayer::PlayingState) {
    game_won_sound_->pause();
  }
  if (sale_sound_->state() == QMediaPlayer::PlayingState) {
    sale_sound_->pause();
  }
  if (not_enough_money_sound_->state() == QMediaPlayer::PlayingState) {
    not_enough_money_sound_->pause();
  }
  if (new_wave_->state() == QMediaPlayer::PlayingState) {
    new_wave_->pause();
  }
}

void MusicPlayer::Resume() {
  current_state_ = CurrentState::kPause;
  if (main_player_->state() == QMediaPlayer::PausedState) {
    main_player_->play();
  }
  if (game_over_sound_->state() == QMediaPlayer::PausedState) {
    game_over_sound_->play();
  }
  if (button_sound_->state() == QMediaPlayer::PausedState) {
    button_sound_->play();
  }
  if (game_won_sound_->state() == QMediaPlayer::PausedState) {
    game_won_sound_->play();
  }
  if (sale_sound_->state() == QMediaPlayer::PausedState) {
    sale_sound_->play();
  }
  if (not_enough_money_sound_->state() == QMediaPlayer::PausedState) {
    not_enough_money_sound_->play();
  }
  if (new_wave_->state() == QMediaPlayer::PausedState) {
    new_wave_->play();
  }
}
