#ifndef SERVER_SERVER_MESSAGE_H_
#define SERVER_SERVER_MESSAGE_H_

#include <QString>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

enum class MessageType {
  kOk = 0,
  kError = 1,
  kNewConnection = 2
};

class ServerMessages {
 public:
  QByteArray NewConnectionMessage(QString nick_name);

  void ToDecode(const QByteArray& array);
  QByteArray ToCode() const;
  QString GetMessage();

 private:
  MessageType type_;
  QString message_;
};

#endif  // SERVER_MESSAGE_H_
