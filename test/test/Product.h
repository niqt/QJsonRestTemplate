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

#include"../../JsonClassInterface.h"
#include<QString>

class Product:public JsonClassInterface {
private:
	int id;
	QString name;

public:
Product();
	int getId();
	QString getName();
	void setId(int id);
	void setName(QString name);
	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;
};
