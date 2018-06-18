#include "AddresBook.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AddresBook w;
	w.show();
	return a.exec();
}
