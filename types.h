#ifndef TYPES_H
#define TYPES_H
#include <QString>

typedef struct {
    QString name;
    QString type;
    QString description;
}JsonItem;

typedef struct {
    QString name;
    QList<JsonItem> fields;
}JsonClass;

#endif // TYPES_H
