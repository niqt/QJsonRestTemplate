#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>
#include "../../qjsonresttemplate.h"
#include "../../JsonClassInterface.h"
#include "Product.h"

class TestObject : public QObject
{
    Q_OBJECT
public:
    explicit TestObject(QObject *parent = 0);

signals:

public slots:
    void readResponse(JsonClassInterface *);
};

#endif // TESTOBJECT_H
