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

#include <QApplication>
#include <QQmlApplicationEngine>
#include "testclass.h"
#include "qjsonresttemplate.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    QJsonRestTemplate  *templateRest = new QJsonRestTemplate();

    TestClass *p = new TestClass();

    //templateRest->post(QUrl("http://10.2.10.51:8080/peppe"), p->toJson());
    templateRest->get(QUrl("http://10.2.10.51:8080/greeting"));
    //connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateProgress(qint64,qint64)));

    return app.exec();
}
