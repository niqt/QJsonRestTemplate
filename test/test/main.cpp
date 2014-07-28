#include <QCoreApplication>
#include "../../qjsonresttemplate.h"
#include "../../JsonClassInterface.h"
#include "Product.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QJsonRestTemplate  *templateRest = new QJsonRestTemplate();
    Product *p = new Product();
    p->setId(1);
    p->setName("pippo");
    templateRest->post(QUrl("http://10.2.10.4:8080/peppe"), p);
    return a.exec();
}
