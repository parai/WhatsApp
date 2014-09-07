#include <QApplication>
#include "entry.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Entry w;
    w.setWindowTitle("WhatsApp<parai@foxmail.com>");
    w.show();

    return a.exec();
}
