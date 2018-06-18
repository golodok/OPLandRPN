#include "AddresBook.h"


AddresBook::AddresBook(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	readFile();
}

void AddresBook::readFile()
{
	DataOfThePerson data;
	QList<DataOfThePerson> qDataList;
	QFile file("DataAdress.csv");
	if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		while (!stream.atEnd()) {
			QString sTmp;
			sTmp = stream.readLine();
			if (sTmp.size() >0 ) {
				parseStrToData(sTmp, data);
				qDataList.push_back(data);
			}
			else break;
		}		
	fullTable(qDataList);
	}
	else {
		qDebug() << "Ошибка при открытии файла";
	}
	file.close();
}

void AddresBook::fullTable(const QList<DataOfThePerson> & qDataList)
{
	int count = 0;
	for each (DataOfThePerson data in qDataList)
	{
		ui.tableWidgetBook->insertRow(count);
		ui.tableWidgetBook->setItem(count, 0, new QTableWidgetItem(data.getName()+ " " + data.getSurname()+ " "+ data.getOtshestvo()));
		ui.tableWidgetBook->setItem(count, 1, new QTableWidgetItem(data.getNumberOfPhone()));
		ui.tableWidgetBook->setItem(count, 2, new QTableWidgetItem(data.getEmail()));
		ui.tableWidgetBook->setItem(count, 3, new QTableWidgetItem(data.getAddress()));
		count++;
	}
	ui.tableWidgetBook->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui.tableWidgetBook->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	ui.tableWidgetBook->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	ui.tableWidgetBook->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
}

DataOfThePerson & AddresBook::getStr(const QStringList & qLdata)
{
	DataOfThePerson data;
	return data;
}

void AddresBook::parseStrToData(const QString & str, DataOfThePerson & data)
{
	QRegExp rx("[;]");
	QStringList lToken = str.split(rx);
	data.setName(lToken[0]);
	data.setSurname(lToken[1]);
	data.setOtshestvo(lToken[2]);
	data.setNumberOfPhone(lToken[3]);
	data.setEmail(lToken[4]);
	data.setAdress(lToken[5]);
}
