#include "paymentwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaymentWindow w;
    w.show();
    return a.exec();
}
