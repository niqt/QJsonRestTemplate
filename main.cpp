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
