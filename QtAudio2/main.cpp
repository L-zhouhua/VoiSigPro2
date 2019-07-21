#include "QtAudio2.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);
	QApplication a(argc, argv);
	QtAudio2 w;
	w.show();
	return a.exec();
}
