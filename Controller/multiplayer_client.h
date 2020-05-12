#ifndef CONTROLLER_MULTIPLAYER_CLIENT_H_
#define CONTROLLER_MULTIPLAYER_CLIENT_H_

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFile>
#include <QSettings>
#include <QWebSocket>

#include <chrono>
#include <list>
#include <vector>
#include <random>

#include "Server/message.h"
#include "Model/constants.h"

// The multiplayer client is responsible for the connection between the game
// and the server.
class MultiplayerClient : public QObject {
  Q_OBJECT

 public:
  MultiplayerClient();
  ~MultiplayerClient() override;

  void Tick(int delta_time);
  void LoadDatabase();
  void Connect();
  void Disconnect();

  // Send
  void SendMessageToServer(const Message& message) const;
  void Register(const QString& nick_name);
  void EnterRoom(int level_id);
  void RoundCompleted(int base_current_health, int completed_game_process);
  void LeaveRoom();

  // Receive
  bool IsReceivedMessageEmpty() const;
  const std::list<Message>& GetReceivedMessage() const;
  void ClearReceivedMessage();

  bool IsRegistered() const;
  void ChangePermissionToStartRound(bool permission);
  bool IsOnline() const;
  bool HasPermissionToStartRound() const;

  void NewClientMessage(const QString& messages);
  void ProcessCommand(QString command);

  void CreateVisibleMessage(const Message& message);

 private slots:  // NOLINT
  void OnConnect();
  void OnMessageReceived(const QByteArray& array);
  void onClose();

 private:
  QString nick_name_ = "";
  QWebSocket* server_web_socket_{};
  // const QString address = "ws://localhost:1234";
  const QString address = "ws://49.12.75.135:1234";
  const int kMaxMessageSize = 30;
  bool is_online_ = false;
  bool is_end_round_message_sent_ = true;
  bool has_permission_to_start_round = true;
  std::list<Message> received_message_;
  static std::mt19937 random_generator_;

  int wait_time_;
  int current_time_;
  bool is_trying_to_connect_ = false;
  const int kWaitTime = 3000;

  std::vector<VisibleMessage> data_base_;

 private:
  QString AutoGenerateNickName() const;
  const QStringList first_name = {"Greedy", "Bloody", "Big", "Mega", "Optimus"};
  const QStringList sur_name = {"finger", "cup", "flex", "cringe", "sage"};
};

#endif  // CONTROLLER_MULTIPLAYER_CLIENT_H_
