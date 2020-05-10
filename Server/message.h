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
  kChatUpdate,
  kNickNameJoinedTheRoom, // % nickname
  kNickNameWinWithHp, // % nickname % hp
  kNickNameFinishRoundWithHp, // % nickname % hp
  kNickNameLeft, // % nickname
  kRoomStartsIn, // % time
  kRoundStartsIn, // % time
  kDialog,
  kControllerCommand,
  kNickNameDead, // % nickname

  // To translate
  kConnect,
  kDisconnect,
  kPlayerMessage, // %message
  kChatOffline,
  kNameNullMessage,
  kErrorCommand,
  kYourNickNameIs, // %nick_name
  kMoreGold,
  kGoldError,
  kInfinityHealth,
  kHintRegistration1,
  kHintRegistration2,
  kYouCreatedRoom,
  kGameEnd,
  kServerClosed,
  kOk

};

enum class DialogTypeArg {

};
// The main class of data transfer between the server and the client.
// The server and client communicate in the language of messages
class Message {
 public:
  Message() = default;
  Message(MessageType type, QStringList arguments = {});
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

  Message& SetControllerMessage(const QString& message, DialogType type,
                                const QString& nick_name = "");

  Message& SetCommandMessage(const QString& message,
                             ControllerCommandType type);
  Message& DecodeFromBinary(const QByteArray& array);
  MessageType GetType() const;
  QString GetArgument(int arg_num) const;
  ControllerCommandType GetControllerCommandType() const;
  DialogType GetDialogType() const;

 private:
  MessageType message_type_;
  DialogType dialog_type_;
  ControllerCommandType controller_command_type_;
  QStringList arguments_;
  int arguments_number_ = 0;

};

#endif  // SERVER_MESSAGE_H_
