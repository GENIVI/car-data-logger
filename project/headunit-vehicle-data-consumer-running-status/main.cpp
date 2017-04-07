#include <QCoreApplication>
#include <csignal>
#include <dlt.h>
#include <CommonAPI/CommonAPI.hpp>
#include "VehicleDataManagerService.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGTERM, [](int sig){ qApp->quit(); });
    signal(SIGINT, [](int sig){ qApp->quit(); });

    DLT_REGISTER_APP("vdm", "Vehicle Data Manager");
    DLT_ENABLE_LOCAL_PRINT();

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    runtime->registerService("local", "com.ivis.VehicleDataManager.VehicleDataManager", VehicleManagerService::instance());

    VehicleManagerService::instance()->initService();

    int result = a.exec();

    runtime->unregisterService("local", VehicleDataManager::getInterface(), "com.ivis.VehicleDataManager.VehicleDataManager");

    VehicleManagerService::finalize();

    DLT_UNREGISTER_APP();

    return result;
}

