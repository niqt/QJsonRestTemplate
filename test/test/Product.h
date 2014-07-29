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
