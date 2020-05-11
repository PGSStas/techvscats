#ifndef CONTROLLER_MULTIPLAYER_CLIENT_H_
#define CONTROLLER_MULTIPLAYER_CLIENT_H_

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QWebSocket>

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
  void SendMessageToServer(const Message& message);
  void Register(QString nick_name);
  void EnterRoom(int level_id);
  void RoundCompleted(int base_current_health, int completed_game_process);
  void LeaveRoom();

  // Receive
  bool IsReceivedMessageEmpty() const;
  const std::list<Message>& GetReceivedMessages() const;
  void ClearReceivedMessage();

  bool IsRegistered() const;
  void SetPermissionToStartRound(bool permission);
  bool IsOnline() const;
  bool HasPermissionToStartRound() const;

  void NewClientMessage(const QString& messages);
  void ProcessCommand(QString command);

  void CreateControllerMessage(const Message& message);
 private slots:  // NOLINT
  void OnConnect();
  void OnMessageReceived(const QByteArray& array);
  void onClose();

 private:
  QString nick_name_ = "";
  QWebSocket* server_web_socket_;
  const QString address = "ws://localhost:1234";
  // const QString address = "ws://49.12.75.135:1234";
  bool is_online_ = false;
  bool has_permission_to_start_round = true;
  bool is_end_round_message_sent_ = true;
  std::list<Message> received_message_;
  static std::mt19937 random_generator_;

 private:
  QString AutoGenerateNickName() const;
  const QStringList first_name = {"Greedy", "Bloody", "Big", "Mega", "Optimus"};
  const QStringList sur_name = {"finger", "cup", "flex", "cringe", "sage"};
};

#endif  // CONTROLLER_MULTIPLAYER_CLIENT_H_
