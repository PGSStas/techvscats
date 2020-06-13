#ifndef SERVER_MESSAGE_H_
#define SERVER_MESSAGE_H_

#include <QStringList>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <utility>

enum class VisibleType {
  kChat,
  kWarning
};

struct VisibleMessage {
  QString message;
  VisibleType type;
};

enum class CommandType {
  kGoldChange,
  kHealthGrow,
  kChatClear,
  kUnlock
};

enum class MessageType {
  // To client
  kChatUpdate,
  kNickNameDead,  // % nickname
  kNickNameJoinedTheRoom,  // % nickname
  kNickNameFinishRoundWithHp,  // % nickname % hp
  kNickNameLeft,  // % nickname
  kNickNameWinWithHp,  // % nickname % hp
  kRoomStartsIn,  // % time
  kRoundStartsIn,  // % time
  kStartRound,

  // To translate
  kConnect,
  kChatOffline,
  kGoldError,
  kDisconnect,
  kErrorCommand,
  kGameEnd,
  kNameNullMessage,
  kHintRegistration1,
  kHintRegistration2,
  kInfinityHealth,
  kMoreGold,
  kOk,
  kServerClosed,
  kYourNickNameIs,  // %nick_name
  kNickNameIsBig,
  kYouCreatedRoom,
  kLeaveRoom,
  kToLongMessage,
  kServerIsUnavailable,
  kGoToRoom,  // % room number
  kNoCheat,
  kHelpGold,
  kHelpImmortal,
  kHelpClear,
  kHelpUnlock,
  kYouTheBest,

  kLastTranslatable,  // To get size of enum

  // To server
  kEnterRoom = 1000,  // % lvl_id
  kGlobalChat = 1001,  // % message
  kNewConnection = 1002,
  kRoundCompletedByPlayer = 1003,  // % base_current_health % game_process

  kLastServer,

  // To controller
  kControllerCommand = 1004,
  kVisibleMessage = 1005,

  kLastController
};

// The main class of data transfer between the server and the client.
// The server and client communicate in the language of messages
class Message {
 public:
  Message() = default;
  explicit Message(MessageType type, QStringList arguments = {});

  static QByteArray CodeToBinary(const Message& message);
  Message& SetVisibleMessage(const QString& message, VisibleType type,
                             const QString& nick_name = "");
  Message& SetCommandMessage(const QString& message,
                             CommandType type);
  Message& DecodeFromBinary(const QByteArray& array);
  MessageType GetType() const;
  QString GetArgument(int arg_num) const;
  const QStringList& GetArguments() const;
  CommandType GetCommandType() const;
  VisibleType GetDialogType() const;

 private:
  MessageType message_type_;
  VisibleType dialog_type_;
  CommandType command_type_;
  QStringList arguments_;
  int arguments_number_ = 0;
};

#endif  // SERVER_MESSAGE_H_
