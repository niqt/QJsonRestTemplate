/*
* This file is part of QJsonRestTemplate
*
* Copyright (C) 2014 Nicola De Filippo.
*
* Contact: Nicola De Filippo <nicola@nicoladefilippo.it> or <nicola.defilippo@lizard-solutions.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
* 02110-1301 USA
*
*/



#ifndef WRITECODE_H
#define WRITECODE_H

#include <QString>


#include "../types.h"
#include <QFile>
#include <QStringList>

class WriteCode
{
protected:
    QStringList defaultType;
    QList<JsonClass> mJsonClasses;

    QString createSetter(QString className, QString name, QString type);
    QString createGetter(QString className, QString name, QString type);
    QString createReadLine(JsonItem field, QString conversion);
    void createRead(QFile &file, JsonClass newClass);
    void createWrite(QFile &file, JsonClass newClass);
    QString createWriteLine(JsonItem field);
    QString createGet(JsonItem field);
    QString createSet(JsonItem field, QString type);

public:
    WriteCode(QList<JsonClass> jsonClasses);
    virtual void write(QString path){;}
};

#endif // WRITECODE_H
