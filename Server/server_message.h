#ifndef SERVER_SERVER_MESSAGE_H_
#define SERVER_SERVER_MESSAGE_H_

#include <QString>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

enum class MessageType {
  kNewConnection = 0
};

class ServerMessages {
 public:
  QByteArray NewConnectionMessage(QString nick_name);

  ServerMessages& ToDecode(const QByteArray& array);
  QByteArray ToCode() const;
  QString GetMessage() const;
  MessageType GetType() const;
 private:
  MessageType type_;
  QString message_;
};

#endif  // SERVER_MESSAGE_H_
