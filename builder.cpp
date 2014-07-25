#include "builder.h"
#include <QFile>
#include <QDebug>


Builder::Builder(QObject *parent) :
    QObject(parent)
{

}

void Builder::parse(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    char buf[1024];
    int numgraf = 0;
    bool prop = false;
    bool newItem = false;
    JsonClass jsonClass;
    JsonItem currentItem;

    while(file.readLine(buf, 1024) != -1)
    {
        QString line(buf);
        //qDebug() << "line " << line << endl;
        if (line.contains("properties")) {
            //qDebug() << "properties\n";
            numgraf++;
            prop = true;
        } else {
            if (prop && (numgraf % 2) == 1) {

                //qDebug() << "items\n";
                if (line.contains(": {")) {
                    qDebug() << "Field " << line << endl;
                    newItem = true;
                    QString jsonName = this->cleanField(line);

                    currentItem.name = jsonName;
                }
                if (line.contains("type") && newItem) {
                    qDebug() << "type " << line << endl;
                    QString jsonType = this->cleanField(line, "type");
                    currentItem.type = jsonType;
                }
                if (line.contains("}") && newItem) {
                    jsonClass.fields.append(currentItem);
                    newItem = false;
                }
            }
        }
    }
    jsonClasses.append(jsonClass);
}

QString Builder::cleanField(QString field, QString other) {
    QString jsonField(field);
    //jsonField = jsonField.trimmed();
    jsonField = jsonField.remove(' ');
    jsonField = jsonField.remove(':');
    jsonField = jsonField.remove('{');
    jsonField = jsonField.remove('\n');
    jsonField.remove(other);
    jsonField = jsonField.remove('"');
    qDebug() << "JSONFIEL " << jsonField << endl;
    return jsonField;
}

void Builder::print()
{
    for (int i = 0; i < jsonClasses.size(); i++) {
        JsonClass currentClass = jsonClasses.at(i);
        qDebug() << "Class name " << currentClass.name << endl;
        qDebug() << "Fields: \n";
        for (int j = 0; j < currentClass.fields.size(); j++) {
            qDebug() << "\t NAME " << currentClass.fields.at(j).name << endl;
            qDebug() << "\t TYPE " << currentClass.fields.at(j).type << endl;
        }
    }
}
