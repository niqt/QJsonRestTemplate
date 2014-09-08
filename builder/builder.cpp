#include "builder.h"
#include <QFile>
#include <QDebug>
#include "writecode.h"
#include "writecplusplusclass.h"


/*!
 * \brief Builder::Builder
 * \param parent
 */


Builder::Builder(QObject *parent) :
    QObject(parent)
{
    defaultType << "char" << "integer" << "boolean";
}

/*!
 * \brief parse the json schema and create JsonClass object
 * \param path of the json schema file
 */

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
        } else if (line.contains("title")) {
            jsonClass.name = this->cleanField(line, "title");
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


/*!
 * \brief Given json schema, create Classes for languages
 * \param schemaPath where is the json schema
 * \param classesPath where to write the classes
 * \param languages for the output classes (only c++ supported)
 * \return
 */

bool Builder::createClasses(QString schemaPath, QString classesPath, QStringList languages)
{
    parse(schemaPath);
    for (int i = 0; i < languages.size(); i++) {
        WriteCode *writer;
        if (languages.at(i) == "c++") {
            writer = new WriteCPlusPlusClass(jsonClasses);
        }
        if (writer) {
            writer->write(classesPath);
            delete writer;
        }
    }
}

/*!
 * \brief print json classes
 */

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

/*!
 * \brief remove bad character from fields class
 * \param field
 * \param other character to remove
 * \return
 */

QString Builder::cleanField(QString field, QString other) {
    QString jsonField(field);

    jsonField = jsonField.remove(' ');
    jsonField = jsonField.remove(':');
    jsonField = jsonField.remove('{');
    jsonField = jsonField.remove('\n');
    jsonField = jsonField.remove(',');
    jsonField.remove(other);
    jsonField = jsonField.remove('"');

    return jsonField;
}
