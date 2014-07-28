#ifndef JSONCLASSINTERFACE_H
#define JSONCLASSINTERFACE_H

#include <QJsonObject>

class JsonClassInterface {
    //JsonClassInterface() {;}
    //virtual ~JsonClassInterface() {;}
public:
    virtual void read(const QJsonObject &json) = 0;
    virtual void write(QJsonObject &json) const = 0;
};

#endif // JSONCLASSINTERFACE_H
