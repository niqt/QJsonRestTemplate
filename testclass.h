#ifndef PEPPE_H
#define PEPPE_H

#include <QString>
#include <QObject>
#include <QNetworkReply>
#include <QJsonDocument>

class TestClass
{

private:
    QString m_username;
    QNetworkReply *reply;
public:
    TestClass();
    QString username() const;
    void setUsername(const QString &name);
    QJsonDocument toJson();

};

#endif // PEPPE_H
