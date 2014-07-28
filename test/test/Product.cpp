#include "Product.h"

Product::Product()
{
}

void Product::setId(int id)
{
    this->id = id;
}

void Product::setName(QString name)
{
    this->name = name;
}

void Product::read(const QJsonObject &json)
{	this->id = json["id"].toInt();
    this->name = json["name"].toString();
}

void Product::write(QJsonObject &json) const
{	json["id"] = this->id;
    json["name"] = this->name;
}
