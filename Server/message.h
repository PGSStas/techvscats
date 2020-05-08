#ifndef SERVER_SERVER_MESSAGE_H_
#define SERVER_SERVER_MESSAGE_H_

#include <QStringList>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

enum class DialogType {
  kChat,
  kWarning
};

enum class MessageType {
  // To server
  kNewConnection = 0,
  kEnterRoom = 1,
  kRoundCompletedByPlayer = 2,
  kLeaveRoom = 3,
  kGlobalChat = 4,
  // To client
  kStartRound = 5,
  kDialog = 6
};

// The main class of data transfer between the server and the client.
// The server and client communicate in the language of messages
class Message {
 public:
  // To server
  QByteArray NewConnectionMessage(const QString& nick_name);
  QByteArray EnterRoomMessage(int level_id);
  QByteArray RoundCompletedMessage(int current_health);
  QByteArray LeaveRoomMessage();
  QByteArray GlobalChatMessage(const QString& messages);

  // To client
  QByteArray StartRoundMessage();
  QByteArray DialogMessage(const QString& message, DialogType type,
                           const QString& nick_name = "");

  Message& SetDialogMessage(const QString& message, DialogType type,
                            const QString& nick_name = "");
  Message& DecodeFromBinary(const QByteArray& array);
  QByteArray CodeToBinary() const;
  MessageType GetType() const;
  QString GetMessage() const;
  int GetNumber() const;

 private:
  MessageType type_;
  QString message_ = "";
  int number_ = 0;
};

#endif  // SERVER_MESSAGE_H_
