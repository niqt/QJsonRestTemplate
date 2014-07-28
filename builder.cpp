#include "builder.h"
#include <QFile>
#include <QDebug>


Builder::Builder(QObject *parent) :
    QObject(parent)
{
    defaultType << "char" << "integer" << "boolean";
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
    writeClass(jsonClass);
}

void Builder::writeClass(JsonClass newClass)
{
    QFile file("/tmp/" + newClass.name + ".h");
    //QFile file("/tmp/" + test.h");
    file.open(QIODevice::WriteOnly);

    writeInclude(file, newClass);
    file.close();
    file.setFileName("/tmp/" + newClass.name + ".cpp");
    file.open(QIODevice::WriteOnly);
    writeBody(file, newClass);
    file.close();
}

void Builder::writeInclude(QFile &file, JsonClass newClass)
{
    //QFile file("/tmp/test.h");

    file.write("#include\"jsonClassInterface.h\"");
    file.write("\n");

    for (int i = 0; i < newClass.fields.size(); i++) {
        if (!defaultType.contains(newClass.fields.at(i).type)) {
            if (newClass.fields.at(i).type == "string") {
                file.write(QString("#include<QString>\n").toStdString().c_str());
                // write QString
            } else {
                // write name type
            }
        }
    }
    file.write("\n");
    file.write(QString("class " + newClass.name +":public JsonClassInterface {\n").toStdString().c_str());
    file.write("private:\n");
    for (int i = 0; i < newClass.fields.size(); i++) {
        if (newClass.fields.at(i).type == "integer") {
           file.write(QString("\tint " + newClass.fields.at(i).name + ";\n").toStdString().c_str());
        }
        else if (newClass.fields.at(i).type == "string") {
            file.write(QString("\tQString " + newClass.fields.at(i).name + ";\n").toStdString().c_str());
            // write QString
        } else {
            file.write(QString("\t" + newClass.fields.at(i).type + " " + newClass.fields.at(i).name + ";\n").toStdString().c_str());
        }

    }

    // write methods

    file.write("\npublic:\n");

    for (int i = 0; i < newClass.fields.size(); i++) {


        if (newClass.fields.at(i).type == "integer") {

           file.write(QString("\tint " + createGet(newClass.fields.at(i)) + ";\n").toStdString().c_str());
        }
        else if (newClass.fields.at(i).type == "string") {
            file.write(QString("\tQString " + createGet(newClass.fields.at(i)) + ";\n").toStdString().c_str());
            // write QString
        } else {
            file.write(QString("\t" + newClass.fields.at(i).type + " " + createGet(newClass.fields.at(i)) + ";\n").toStdString().c_str());
        }

    }
    file.write(QString("\tvoid read(const QJsonObject &json)\n").toStdString().c_str());
    file.write(QString("\tvoid write(QJsonObject &json) const;\n").toStdString().c_str());
    file.write("}\n");
}

void Builder::writeBody(QFile &file, JsonClass newClass)
{
    file.write(QString("#include<" + newClass.name + ".h>\n\n").toStdString().c_str());

    file.write(QString(newClass.name + "::" + newClass.name +"()\n{\n}\n\n").toStdString().c_str());

    for (int i = 0; i < newClass.fields.size(); i++) {
        if (newClass.fields.at(i).type == "integer") {
           file.write(QString(createSetter(newClass.name, newClass.fields.at(i).name, "int") + "\n\n").toStdString().c_str());
        }
        else if (newClass.fields.at(i).type == "string") {
            file.write(QString(createSetter(newClass.name, newClass.fields.at(i).name, "QString") + "\n\n").toStdString().c_str());
            // write QString
        } else {
            file.write(QString(createSetter(newClass.name, newClass.fields.at(i).name, newClass.fields.at(i).type) + "\n\n").toStdString().c_str());
        }

    }

    for (int i = 0; i < newClass.fields.size(); i++) {
        if (newClass.fields.at(i).type == "integer") {
           file.write(QString(createGetter(newClass.name, newClass.fields.at(i).name, "int") + "\n\n").toStdString().c_str());
        }
        else if (newClass.fields.at(i).type == "string") {
            file.write(QString(createGetter(newClass.name, newClass.fields.at(i).name, "QString") + "\n\n").toStdString().c_str());
            // write QString
        } else {
            file.write(QString(createGetter(newClass.name, newClass.fields.at(i).name, newClass.fields.at(i).type) + "\n\n").toStdString().c_str());
        }

    }

    createRead(file, newClass);
    file.write("\n\n");

    createWrite(file, newClass);
}


void Builder::createRead(QFile &file, JsonClass newClass)
{
    file.write(QString("void " + newClass.name + "::read(const QJsonObject &json)\n{").toStdString().c_str());

    for (int i = 0; i < newClass.fields.size(); i++) {
        if (newClass.fields.at(i).type == "integer") {
           file.write(QString("\t" + createReadLine(newClass.fields.at(i), ".toInt()") + ";\n").toStdString().c_str());
        }
        else if (newClass.fields.at(i).type == "string") {
            file.write(QString("\t" + createReadLine(newClass.fields.at(i), ".toString()") + ";\n").toStdString().c_str());

        } else {
            //
        }

    }

    file.write("}");
}



void Builder::createWrite(QFile &file, JsonClass newClass)
{
    file.write(QString("void " + newClass.name + "::write(QJsonObject &json) const\n{").toStdString().c_str());

    for (int i = 0; i < newClass.fields.size(); i++) {
        if (newClass.fields.at(i).type == "integer") {
           file.write(QString("\t" + createWriteLine(newClass.fields.at(i)) + ";\n").toStdString().c_str());
        }
        else if (newClass.fields.at(i).type == "string") {
            file.write(QString("\t" + createWriteLine(newClass.fields.at(i)) + ";\n").toStdString().c_str());

        } else {
            //
        }

    }

    file.write("}");
}

QString Builder::createReadLine(JsonItem field, QString conversion)
{
    QString line = QString("this->" + field.name + " = json[\"" + field.name + "\"]"+ conversion);
    return line;
}

QString Builder::createWriteLine(JsonItem field)
{
    QString line = QString("json[\"" + field.name + "\"] = this->"+ field.name);
    return line;
}

QString Builder::createGet(JsonItem field)
{
    QString name = field.name;
    QString upper = name.at(0).toUpper() + name.mid(1);
    QString nameMethod = "get" + upper+ "()";
    return nameMethod;
}


QString Builder::createSetter(QString className, QString name, QString type)
{
    QString upper = name.at(0).toUpper() + name.mid(1);
    QString nameMethod = "void " + className + "::set" + upper + "(" + type + " " + name + ")\n";
    QString body = QString("{") + QString("\n\t") + "this->" + name + " = " + name + ";\n}";
    return (nameMethod + body);
}

QString Builder::createGetter(QString className, QString name, QString type)
{
    QString upper = name.at(0).toUpper() + name.mid(1);
    QString nameMethod = type + " " + className + "::get" + upper + "()\n";
    QString body = QString("\t return ") + "this->" + name + ";\n}";
    return (nameMethod + body);
}

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
