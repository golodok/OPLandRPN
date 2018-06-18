#pragma once
#include "DataOfThePerson.h"
#include <QtWidgets/QMainWindow>
#include "ui_AddresBook.h"
#include "sstream"
#include <QFile.h>
#include <QTextStream>
#include <qdebug.h>
#include <QList>

class AddresBook : public QMainWindow
{
	Q_OBJECT

public:
	AddresBook(QWidget *parent = Q_NULLPTR);

private:
	void readFile();
	void fullTable(const QList<DataOfThePerson>   &);
	DataOfThePerson & getStr(const QStringList  &);
	void parseStrToData(const QString &,DataOfThePerson &);
	Ui::AddresBookClass ui;
};
