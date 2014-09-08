#include <QApplication>
#include <QQmlApplicationEngine>
#include "builder.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    Builder builder;

    QStringList languages;
    languages << "c++";
    builder.createClasses("/home/nicola/schema.json", "/tmp/",languages);
    builder.print();


    return app.exec();
}
