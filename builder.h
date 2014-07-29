#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include "types.h"
#include <QStringList>
#include <QFile>

class Builder : public QObject
{
    Q_OBJECT
private:
    QList<JsonClass> jsonClasses;
    QStringList defaultType;

    QString cleanField(QString field, QString other = 0);
    void writeInclude( QFile &file, JsonClass newClass);
    void writeBody(QFile &file, JsonClass newClass);
    QString createGet(JsonItem field);
    QString createSet(JsonItem field, QString type);
    QString createSetter(QString className, QString name, QString type);
    QString createGetter(QString className, QString name, QString type);
    QString createReadLine(JsonItem field, QString conversion);
    void createRead(QFile &file, JsonClass newClass);
    void createWrite(QFile &file, JsonClass newClass);
    QString createWriteLine(JsonItem field);

public:
    explicit Builder(QObject *parent = 0);
    void parse(QString path);
    void print();
    void writeClass(JsonClass newClass);
signals:

public slots:

};

#endif // BUILDER_H
