#include "writecplusplusclass.h"

/*!
 * \brief WriteCPlusPlusClass::WriteCPlusPlusClass
 * \param jsonClasses to transform in C++
 */

WriteCPlusPlusClass::WriteCPlusPlusClass(QList<JsonClass> jsonClasses): WriteCode(jsonClasses)
{
}


/*!
 * \brief write c++ .h and c++ in path
 * \param The place where found the c++ files
 */

void WriteCPlusPlusClass::write(QString path)
{
    for (int i = 0; i < this->mJsonClasses.size(); i++) {
        JsonClass newClass = this->mJsonClasses.at(i);
        QFile file(path + newClass.name + ".h");

        file.open(QIODevice::WriteOnly);

        writeInclude(file, newClass);
        file.close();
        file.setFileName(path + newClass.name + ".cpp");
        file.open(QIODevice::WriteOnly);
        writeBody(file, newClass);
        file.close();
    }
}

/*!
 * \brief Write .h
 * \param file is the .h
 * \param newClass class to transform
 */


void WriteCPlusPlusClass::writeInclude(QFile &file, JsonClass newClass)
{
    //QFile file("/tmp/test.h");

    file.write("#include\"../../JsonClassInterface.h\"");
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

    file.write(QString(QString("\t") + newClass.name +"();\n").toStdString().c_str());

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

    for (int i = 0; i < newClass.fields.size(); i++) {


        if (newClass.fields.at(i).type == "integer") {

           file.write(QString("\t" + createSet(newClass.fields.at(i), "int") + ";\n").toStdString().c_str());
        }
        else if (newClass.fields.at(i).type == "string") {
            file.write(QString("\t" + createSet(newClass.fields.at(i), "QString") + ";\n").toStdString().c_str());
            // write QString
        } else {
            file.write(QString("\t" + createSet(newClass.fields.at(i), newClass.fields.at(i).type) + ";\n").toStdString().c_str());
        }

    }

    file.write(QString("\tvoid read(const QJsonObject &json);\n").toStdString().c_str());
    file.write(QString("\tvoid write(QJsonObject &json) const;\n").toStdString().c_str());
    file.write("};\n");
}



/*!
 * \brief Write .cpp
 * \param file the .cpp file
 * \param newClass to transform
 */

void WriteCPlusPlusClass::writeBody(QFile &file, JsonClass newClass)
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

