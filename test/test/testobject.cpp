#include "testobject.h"
#include <QDebug>

TestObject::TestObject(QObject *parent) :
    QObject(parent)
{
    QJsonRestTemplate  *templateRest = new QJsonRestTemplate();
    Product *p = new Product();
    //p->setId(1);
    //p->setName("pippo");
    //templateRest->post(QUrl("http://10.2.10.4:8080/peppe"), p);
    connect(templateRest, SIGNAL(readResponse(JsonClassInterface *)), this, SLOT(readResponse(JsonClassInterface *)));
    templateRest->get(QUrl("http://10.2.10.4:8080/peppeget"), p);
}

void TestObject::readResponse(JsonClassInterface *a)
{
    Product *p = (Product *) a;
    qDebug() << " NAME = " << p->getName() << " ID " << p->getId() << endl;
}
