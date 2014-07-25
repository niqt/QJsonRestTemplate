#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include "types.h"

class Builder : public QObject
{
    Q_OBJECT
private:
    QList<JsonClass> jsonClasses;
    QString cleanField(QString field, QString other = 0);
public:
    explicit Builder(QObject *parent = 0);
    void parse(QString path);
    void print();
signals:

public slots:

};

#endif // BUILDER_H
