#include "multiplayer_client.h"

void MultiplayerClient::SetIsOnline(bool is_online) {
  is_online_ = is_online;
}

MultiplayerClient::~MultiplayerClient() {
  Close();
}

void MultiplayerClient::Connect() {
  web_socket_ = new QWebSocket();
  connect(web_socket_, &QWebSocket::connected,
          this, &MultiplayerClient::onConnected);
  connect(web_socket_, &QWebSocket::disconnected,
          this, &MultiplayerClient::onClose);
  web_socket_->open(QUrl(address));
  qDebug() << "Start connection...";
}

void MultiplayerClient::Close() {
  web_socket_->close();
  web_socket_->deleteLater();
}

void MultiplayerClient::onConnected() {
  qDebug() << "It works!";
  connect(web_socket_, &QWebSocket::textMessageReceived,
          this, &MultiplayerClient::onTextMessageReceived);
  web_socket_->sendTextMessage(ServerMessage().ToCode());
  is_online_ = true;
}

void MultiplayerClient::onTextMessageReceived(QString message) {
  ServerMessage new_message;
  new_message.ToDecode(message);
  messages_.push_back(new_message);
  qDebug() << "new message " << message;
}

void MultiplayerClient::onClose() {
  qDebug() << "server killed you";
  is_online_ = false;
}
