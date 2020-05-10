#ifndef SERVER_MESSAGE_H_
#define SERVER_MESSAGE_H_

#include <QStringList>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

enum class DialogType {
  kChat,
  kWarning
};

enum class ControllerCommandType {
  kGoldChange,
  kHealthGrow,
};

enum class MessageType {
  // To server
  kNewConnection,
  kEnterRoom,
  kRoundCompletedByPlayer,
  kLeaveRoom,
  kGlobalChat,
  // To client
  kStartRound,
  kDialog,
  kControllerCommand
};

// The main class of data transfer between the server and the client.
// The server and client communicate in the language of messages
class Message {
 public:
  Message() = default;
  Message(MessageType type, const QString& message, int number);
  // To server
  static QByteArray NewConnectionMessage(const QString& nick_name);
  static QByteArray EnterRoomMessage(int level_id);
  static QByteArray RoundCompletedMessage(int current_health,
                                          int casted_game_process);
  static QByteArray LeaveRoomMessage();
  static QByteArray GlobalChatMessage(const QString& messages);

  // To client
  static QByteArray StartRoundMessage();
  static QByteArray DialogMessage(const QString& message, DialogType type,
                                  const QString& nick_name = "");

  static QByteArray CodeToBinary(const Message& message);

  Message& SetDialogMessage(const QString& message, DialogType type,
                            const QString& nick_name = "");

  Message& SetCommandMessage(const QString& message,
                             ControllerCommandType type);
  Message& DecodeFromBinary(const QByteArray& array);
  MessageType GetType() const;
  QString GetMessage() const;
  int GetNumber() const;

 private:
  MessageType type_;
  QString message_ = "";
  int number_ = 0;
};

#endif  // SERVER_MESSAGE_H_
