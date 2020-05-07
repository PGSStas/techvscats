#ifndef SERVER_SERVER_MESSAGE_H_
#define SERVER_SERVER_MESSAGE_H_

#include <QString>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

enum class MessageType {
  // To server
  kNewConnection = 0,
  kEnterRoom = 1,
  // To client
  kStartRound = 2
};

class Message {
 public:
  // To server
  QByteArray NewConnectionMessage(QString nick_name);
  QByteArray EnterRoomMessage(int level_id);
  // To client
  QByteArray StartRoundMessage();

  Message& ToDecode(const QByteArray& array);
  QByteArray ToCode() const;
  MessageType GetType() const;
  QString GetMessage() const;
  int GetNumber() const;

 private:
  MessageType type_;
  QString message_ = "";
  int number_ = 0;
};

#endif  // SERVER_MESSAGE_H_
