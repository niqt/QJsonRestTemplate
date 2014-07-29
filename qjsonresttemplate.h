#ifndef QJSONRESTTEMPLATE_H
#define QJSONRESTTEMPLATE_H

/*
* This file is part of QJsonRestTemplate
*
* Copyright (C) 2014 Nicola De Filippo.
*
* Contact: Nicola De Filippo <nicola@nicoladefilippo.it> or <nicola.defilippo@lizard-solutions.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
* 02110-1301 USA
*
*/

#include <QObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include "JsonClassInterface.h"

class QJsonRestTemplate : public QObject
{
    Q_OBJECT
private:
    QNetworkReply *mReply;
    QNetworkAccessManager *mManager;
    QNetworkRequest mReq;
    JsonClassInterface *mResult;

    QByteArray prepareNetwork(QUrl url, QJsonDocument doc);
    void prepareNetwork(QUrl url);

    void connectReplySlots();
public:
    explicit QJsonRestTemplate(QObject *parent = 0);
    void post(QUrl, QJsonDocument);
    void post(QUrl, JsonClassInterface *a);
    void get(QUrl);
    void get(QUrl, JsonClassInterface *a);
signals:
    //QJsonDocument readResponse();
    //QJsonDocument postResponse();
    void readResponse(JsonClassInterface*);
    JsonClassInterface* postResponse();
public slots:
    void error(QNetworkReply::NetworkError error);
    void finished();
    void updateProgress(qint64 c , qint64 t);

};

#endif // QJSONRESTTEMPLATE_H
