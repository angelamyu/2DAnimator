#include "opengldemo.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OpenGLDemo w;
	w.show();
	return a.exec();
}
