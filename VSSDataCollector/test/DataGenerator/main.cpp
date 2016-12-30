#include <QCoreApplication>
#include <csignal>

#include "datagenerator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

    DataGenerator dataGenerator;

    dataGenerator.start();

    int result = a.exec();

    dataGenerator.stop();

    return result;
}
