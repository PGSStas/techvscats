#include "multiplayer_client.h"

MultiplayerClient::~MultiplayerClient() {
  Close();
}

void MultiplayerClient::Connect() {
  web_socket_ = new QWebSocket();
  connect(web_socket_, &QWebSocket::connected,
          this, &MultiplayerClient::OnConnect);
  connect(web_socket_, &QWebSocket::disconnected,
          this, &MultiplayerClient::onClose);
  web_socket_->open(QUrl(address));
}

void MultiplayerClient::Close() {
  web_socket_->close();
  web_socket_->deleteLater();
}

void MultiplayerClient::OnConnect() {
  qDebug() << "Connected!!!";
  connect(web_socket_, &QWebSocket::binaryMessageReceived,
          this, &MultiplayerClient::OnMessageReceived);
  is_online_ = true;
  nick_name_ = AutoGenerateNickName();
  web_socket_->sendBinaryMessage(ServerMessages().NewConnectionMessage(
      nick_name_));
  is_online_ = true;
}

void MultiplayerClient::OnMessageReceived(const QByteArray& array) {
  ServerMessages new_message;
  new_message.ToDecode(array);
  messages_.push_back(new_message);
  qDebug() << "new message " << new_message.GetMessage();
}

void MultiplayerClient::onClose() {
  qDebug() << "server killed you";
  is_online_ = false;
}

QString MultiplayerClient::AutoGenerateNickName() const {
  return first_name[qrand() % first_name.size()]+"_"
      + sur_name[qrand() % sur_name.size()];
}
