#include "qjsonresttemplate.h"

QJsonRestTemplate::QJsonRestTemplate(QObject *parent) :
    QObject(parent)
{
}

void QJsonRestTemplate::post(QUrl url, QJsonDocument doc)
{
    QByteArray postData = prepareNetwork(url, doc);

    mReply = mManager->post(mReq, postData);

    connectReplySlots();
}

void QJsonRestTemplate::post(QUrl url, JsonClassInterface *a)
{
    QJsonObject jsonObject;
    a->write(jsonObject);
    const QJsonDocument doc(jsonObject);

    QByteArray postData = prepareNetwork(url, doc);

    mReply = mManager->post(mReq, postData);
    connectReplySlots();
}

QByteArray QJsonRestTemplate::prepareNetwork(QUrl url, QJsonDocument doc)
{
    QByteArray postData;

    postData = doc.toJson();

    QByteArray postDataSize = QByteArray::number(postData.size());

    mManager = new QNetworkAccessManager();

    mReq.setUrl(url);
    mReq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    mReq.setRawHeader("Content-Length", postDataSize);

    return postData;
}

void QJsonRestTemplate::prepareNetwork(QUrl url)
{
    QByteArray postData;

    QByteArray postDataSize = QByteArray::number(postData.size());

    mManager = new QNetworkAccessManager();

    mReq.setUrl(url);
    mReq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    mReq.setRawHeader("Content-Length", postDataSize);

}

void QJsonRestTemplate::connectReplySlots()
{
    connect(mReply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateProgress(qint64,qint64)));
    connect(mReply,SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    connect(mReply,SIGNAL(finished()), this, SLOT(finished()));
}

void QJsonRestTemplate::get(QUrl url)
{
    prepareNetwork(url);
    mReply = mManager->get(mReq);
    connectReplySlots();
}

void QJsonRestTemplate::get(QUrl url, JsonClassInterface *a)
{
    mResult = a;
    prepareNetwork(url);
    mReply = mManager->get(mReq);
    connectReplySlots();
}

void QJsonRestTemplate::updateProgress(qint64 c , qint64 t)
{
    qDebug() << "Cu = " << c << " tot " << t << endl;
}



void QJsonRestTemplate::finished()
{

    QString dum = (QString) mReply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(dum.toUtf8());
    mResult->read(doc.object());
    emit readResponse(mResult);
}

void QJsonRestTemplate::error(QNetworkReply::NetworkError error)
{
    qDebug() << "Error " << error << endl;
}
