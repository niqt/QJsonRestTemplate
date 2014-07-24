#include "testclass.h"
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QDebug>


TestClass::TestClass()
{
}



void TestClass::setUsername(const QString &name)
{
    m_username = name;
}


QString TestClass::username() const
{
    return m_username;
}

QJsonDocument TestClass::toJson()
{
    QVariantMap top;
    top.insert( "username", QString( "test@gmail.com" ) );

    const QJsonDocument doc = QJsonDocument::fromVariant(top);
    return doc;
}
