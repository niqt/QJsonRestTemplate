#include "qjsonresttemplate.h"


/*!
 * \brief Constructor
 * \param parent
 */

QJsonRestTemplate::QJsonRestTemplate(QObject *parent) :
    QObject(parent)
{
}


/*!
 * \brief Post json document to url
 * \param url the url
 * \param doc JsonDocument to post
 */


void QJsonRestTemplate::post(QUrl url, QJsonDocument doc)
{
    QByteArray postData = prepareNetwork(url, doc);

    mReply = mManager->post(mReq, postData);

    connectReplySlots();
}

/*!
 * \brief Post JsonClassInterca object to url
 * \param url the url
 * \param a the JsonClassInterface object
 */

void QJsonRestTemplate::post(QUrl url, JsonClassInterface *a)
{
    QJsonObject jsonObject;
    a->write(jsonObject);
    const QJsonDocument doc(jsonObject);

    QByteArray postData = prepareNetwork(url, doc);

    mReply = mManager->post(mReq, postData);
    connectReplySlots();
}


/*!
 * \brief Prepare network and data to send
 * \param url the url
 * \param doc the JsonDocumenentto send
 * \return http data to send
 */

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

/*!
 * \brief Prepare network
 * \param url the url for network operation
 */

void QJsonRestTemplate::prepareNetwork(QUrl url)
{
    QByteArray postData;

    QByteArray postDataSize = QByteArray::number(postData.size());

    mManager = new QNetworkAccessManager();

    mReq.setUrl(url);
    mReq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    mReq.setRawHeader("Content-Length", postDataSize);

}

/*!
 * \brief Connect slots for newtwork reply
 */

void QJsonRestTemplate::connectReplySlots()
{
    connect(mReply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateProgress(qint64,qint64)));
    connect(mReply,SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    connect(mReply,SIGNAL(finished()), this, SLOT(finished()));
}


/*!
 * \brief Get for JSonDocument
 * \param url the url
 */

void QJsonRestTemplate::get(QUrl url)
{
    prepareNetwork(url);
    mReply = mManager->get(mReq);
    connectReplySlots();
}

/*!
 * \brief Get JsonClassInterface object
 * \param url the url
 * \param a the object tha will contain the data
 */

void QJsonRestTemplate::get(QUrl url, JsonClassInterface *a)
{
    mResult = a;
    prepareNetwork(url);
    mReply = mManager->get(mReq);
    connectReplySlots();
}


/*!
 * \brief Slot for update network operation
 * \param c current byte transferred
 * \param t total byte of the object
 */


void QJsonRestTemplate::updateProgress(qint64 c , qint64 t)
{
    qDebug() << "Cu = " << c << " tot " << t << endl;
}


/*!
 * \brief Slot per finished operation success
 */

void QJsonRestTemplate::finished()
{

    QString dum = (QString) mReply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(dum.toUtf8());
    mResult->read(doc.object());
    emit readResponse(mResult);
}

/*!
 * \brief Slot for error
 * \param error the network error
 */

void QJsonRestTemplate::error(QNetworkReply::NetworkError error)
{
    qDebug() << "Error " << error << endl;
}
