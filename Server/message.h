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
  kEnterRoom,  // % lvl_id
  kGlobalChat, // % message
  kLeaveRoom,
  kNewConnection,
  kRoundCompletedByPlayer, // % base_current_health % casted game_process

  // To client
  kControllerCommand,
  kChatUpdate,
  kNickNameDead, // % nickname
  kNickNameJoinedTheRoom,  // % nickname
  kNickNameFinishRoundWithHp, // % nickname % hp
  kNickNameLeft, // % nickname
  kNickNameWinWithHp, // % nickname % hp
  kRoomStartsIn, // % time
  kRoundStartsIn, // % time
  kStartRound,

  // To translate
  kConnect,
  kChatOffline,
  kControllerMessage,
  kGoldError,
  kDisconnect,
  kErrorCommand,
  kGameEnd,
  kNameNullMessage,
  kHintRegistration1,
  kHintRegistration2,
  kInfinityHealth,
  kPlayerMessage, // %message
  kMoreGold,
  kOk,
  kServerClosed,
  kYourNickNameIs, // %nick_name
  kYouCreatedRoom,
};

enum class DialogTypeArg {

};
// The main class of data transfer between the server and the client.
// The server and client communicate in the language of messages
class Message {
 public:
  Message() = default;
  Message(MessageType type, QStringList arguments = {});

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
