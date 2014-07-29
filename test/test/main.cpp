#include <QCoreApplication>

#include "testobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TestObject *o = new TestObject();
    return a.exec();
}
