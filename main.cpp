#include <QApplication>
#include "ssrtools.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ssrtools ssr;
    ssr.show();
    return a.exec();
}
