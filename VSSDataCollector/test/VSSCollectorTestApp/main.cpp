#include <vssdatacollector.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <csignal>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

    QString currentPath = QDir::currentPath();

    setenv("VSS_JSON_FILE", (QString("%1/vss_rel_1.json").arg(currentPath)).toStdString().data(), 1);
    setenv("VSS_COLLECTOR_CONFIGURATION_FILE", (QString("%1/DataConfig.json").arg(currentPath)).toStdString().data(), 1);
    setenv("VSS_VSI_FILE", (QString("%1/vss_rel_1.vsi").arg(currentPath)).toStdString().data(), 1);

    VSSDataCollector vssDataCollector_instance;

    if( !vssDataCollector_instance.start() )
    {
        qDebug() << "Vss Data Collector Daemon Error";
        return 0;
    }

    int result = a.exec();

    vssDataCollector_instance.stop();

    return result;
}
