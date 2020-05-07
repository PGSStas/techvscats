#ifndef CONTROLLER_MULTIPLAYER_CLIENT_H_
#define CONTROLLER_MULTIPLAYER_CLIENT_H_

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtWebSockets/QWebSocket>

#include <chrono>
#include <list>
#include <random>

#include "Server/message.h"

class MultiplayerClient : public QObject {
 Q_OBJECT

 public:
  ~MultiplayerClient();

  void Connect();
  void Close();

  void EnterRoom(int level_id);

  bool IsMessagesEmpty() const;
  const std::list<Message>& GetMessages() const;
  void MessagesClear();

  void SetIsReady(bool is_ready);
  bool IsOnline() const;
  bool IsReady() const;

 private Q_SLOTS:
  void OnConnect();
  void OnMessageReceived(const QByteArray& array);
  void onClose();

 private:
  QString nick_name_;
  QWebSocket* web_socket_;
  const QString address = "ws://localhost:1234";
  bool is_online_ = false;
  bool is_ready_ = true;
  std::list<Message> messages_;
  static std::mt19937 random_generator_;

 private:
  QString AutoGenerateNickName() const;
  const QStringList first_name = {"Greedy", "Bloody", "Big", "Mega", "Optimus"};
  const QStringList sur_name = {"finger", "cup", "flex", "cringe", "sage"};
};

#endif  // CONTROLLER_MULTIPLAYER_CLIENT_H_
