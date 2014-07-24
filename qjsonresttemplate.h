#ifndef QJSONRESTTEMPLATE_H
#define QJSONRESTTEMPLATE_H

#include <QObject>
#include <QNetworkReply>
#include<QJsonDocument>

class QJsonRestTemplate : public QObject
{
    Q_OBJECT
private:
    QNetworkReply *mReply;
    QNetworkAccessManager *mManager;
    QNetworkRequest mReq;

    QByteArray prepareNetwork(QUrl url, QJsonDocument doc);
    void prepareNetwork(QUrl url);

    void connectReplySlots();
public:
    explicit QJsonRestTemplate(QObject *parent = 0);
    void post(QUrl, QJsonDocument);
    void get(QUrl);
signals:
    QJsonDocument readResponse();
    QJsonDocument postResponse();
public slots:
    void error(QNetworkReply::NetworkError error);
    void finished();
    void updateProgress(qint64 c , qint64 t);

};

#endif // QJSONRESTTEMPLATE_H
