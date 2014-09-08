#include "writecode.h"


/*!
 * \brief Constructor
 * \param jsonClasses to write
 */

WriteCode::WriteCode(QList<JsonClass> jsonClasses)
{
    defaultType << "char" << "integer" << "boolean";
    mJsonClasses = jsonClasses;
}


/*!
 * \brief Create read method
 * \param file the .cpp file
 * \param newClass class to write
 */

void WriteCode::createRead(QFile &file, JsonClass newClass)
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

/*!
 * \brief Create write method
 * \param file the .cpp file
 * \param newClass class to write
 */

void WriteCode::createWrite(QFile &file, JsonClass newClass)
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

/*!
 * \brief Create readLine for the read method
 * \param field field name
 * \param conversion conversion function
 * \return
 */

QString WriteCode::createReadLine(JsonItem field, QString conversion)
{
    QString line = QString("this->" + field.name + " = json[\"" + field.name + "\"]"+ conversion);
    return line;
}


/*!
 * \brief Create writeLine for the write method
 * \param field field name
 * \return
 */

QString WriteCode::createWriteLine(JsonItem field)
{
    QString line = QString("json[\"" + field.name + "\"] = this->"+ field.name);
    return line;
}

/*!
 * \brief Create getter for .h
 * \param field for getter
 * \return
 */

QString WriteCode::createGet(JsonItem field)
{
    QString name = field.name;
    QString upper = name.at(0).toUpper() + name.mid(1);
    QString nameMethod = "get" + upper+ "()";
    return nameMethod;
}


/*!
 * \brief Create setter for .h
 * \param field for setter
 * \param type return type
 * \return
 */

QString WriteCode::createSet(JsonItem field, QString type)
{
    QString name = field.name;
    QString upper = name.at(0).toUpper() + name.mid(1);
    QString nameMethod = "void set" + upper + "(" + type + " " + field.name + ")";
    return nameMethod;
}

/*!
 * \brief Create setter for .cpp file
 * \param className Class name for setter
 * \param name name of setter
 * \param type type of field
 * \return
 */


QString WriteCode::createSetter(QString className, QString name, QString type)
{
    QString upper = name.at(0).toUpper() + name.mid(1);
    QString nameMethod = "void " + className + "::set" + upper + "(" + type + " " + name + ")\n";
    QString body = QString("{") + QString("\n\t") + "this->" + name + " = " + name + ";\n}";
    return (nameMethod + body);
}

/*!
 * \brief Create gette in .cpp file
 * \param className Class name for getter
 * \param name name of setter
 * \param type type of field
 * \return
 */

QString WriteCode::createGetter(QString className, QString name, QString type)
{
    QString upper = name.at(0).toUpper() + name.mid(1);
    QString nameMethod = type + " " + className + "::get" + upper + "()\n{\n";
    QString body = QString("\t return ") + "this->" + name + ";\n}";
    return (nameMethod + body);
}

