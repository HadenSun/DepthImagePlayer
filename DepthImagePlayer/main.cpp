#include "depthimageplayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DepthImagePlayer w;
	w.show();
	return a.exec();
}
