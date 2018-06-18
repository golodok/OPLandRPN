#pragma once
#include "DataOfThePerson.h"
#include <QtWidgets/QMainWindow>

// Мы не используем дизайнер. Код дизайнера очень плохо поддерживается.address
// Переписать руками.
#include "ui_AddresBook.h" 
#include "sstream"
#include <QFile.h>
#include <QTextStream>
#include <qdebug.h>
#include <QList>

// Нельзя смешивать модель и представления
// Вычитка и хранение данных жолжна быть отделена от представления.address
// Представление должно использовать модель
class AddresBook : public QMainWindow
{
	Q_OBJECT

public:
	AddresBook(QWidget *parent = Q_NULLPTR);

private:
	void readFile(); // Почему я не могу указать, какой файл хочу читать?
	void fullTable(const QList<DataOfThePerson>   &); // Не понятно, что это значит
	DataOfThePerson & getStr(const QStringList  &); // Не должно быть кода, который не используется!
	void parseStrToData(const QString &,DataOfThePerson &); // По возможности избегай инициализации через ссылку. Лучше вернуть новый объект
	Ui::AddresBookClass ui;
};
