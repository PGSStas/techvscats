#ifndef CONTROLLER_MULTIPLAYER_CLIENT_H_
#define CONTROLLER_MULTIPLAYER_CLIENT_H_

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtWebSockets/QWebSocket>

#include <list>

#include "Model/server_message.h"

class MultiplayerClient : public QObject {
  Q_OBJECT

 public:
  ~MultiplayerClient();
  void SetIsOnline(bool is_online);
  void Connect();
  void Close();

 private Q_SLOTS:
  void onConnected();
  void onTextMessageReceived(QString message);
  void onClose();

 private:
  QWebSocket* web_socket_;
  const QString address = " ws://localhost:1234";
  bool is_online_ = false;

  std::list<ServerMessage> messages_;
};

#endif  // CONTROLLER_MULTIPLAYER_CLIENT_H_
