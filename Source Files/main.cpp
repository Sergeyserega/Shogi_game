#include <QApplication>
#include "startwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    StartWindow startWindow;
    startWindow.show();
    return app.exec();
}
