#include "vehicledatagenerator.h"

#include <QCoreApplication>
#include <QDir>
#include <csignal>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

    QString currentPath = QDir::currentPath();

    setenv("STORE_CONFIG_FILE", (QString("%1/store_config_file.json").arg(currentPath)).toStdString().data(), 1);

    vehicleDataGenerator *dataGenerator_instance = new vehicleDataGenerator();

    dataGenerator_instance->init();

    int result = a.exec();

    delete dataGenerator_instance;

    return result;
}
