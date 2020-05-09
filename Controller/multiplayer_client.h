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

// The multiplayer client is responsible for the connection between the game
// and the server.
class MultiplayerClient : public QObject {
 Q_OBJECT

 public:
  ~MultiplayerClient() override;

  void Connect();
  void Disconnect();

  // Send
  void Register(QString nick_name);
  void EnterRoom(int level_id);
  void RoundCompleted(int base_current_health);
  void LeaveRoom();

  // Receive
  bool IsReceivedMessagesEmpty() const;
  const std::list<Message>& GetReceivedMessages() const;
  void ReceivedMessagesClear();

  void SetIsReady(bool is_ready);
  bool IsOnline() const;
  bool IsReady() const;

  void NewClientMessage(const QString& messages);
  void ProcessCommand(QString command);

 private slots:  // NOLINT
  void OnConnect();
  void OnMessageReceived(const QByteArray& array);
  void onClose();

 private:
  QString nick_name_ = "";
  QWebSocket* web_socket_;
  //  const QString address = "ws://localhost:1234";
  const QString address = "ws://49.12.75.135:1234";
  bool is_online_ = false;
  bool is_ready_ = true;
  bool is_send_ = true;
  std::list<Message> received_messages_;
  static std::mt19937 random_generator_;

 private:
  QString AutoGenerateNickName() const;
  const QStringList first_name = {"Greedy", "Bloody", "Big", "Mega", "Optimus"};
  const QStringList sur_name = {"finger", "cup", "flex", "cringe", "sage"};
};

#endif  // CONTROLLER_MULTIPLAYER_CLIENT_H_
