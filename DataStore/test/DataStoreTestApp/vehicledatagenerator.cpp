#include "vehicledatagenerator.h"

vehicleDataGenerator::vehicleDataGenerator(QObject *parent)
    :QObject(parent)
    ,m_storeManager_instance(NULL), m_count(0)
{

}

vehicleDataGenerator::~vehicleDataGenerator()
{
    m_timer->stop();
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(insertData()));
    delete m_timer;

    m_storeManager_instance->stop();
    delete m_storeManager_instance;
}

void vehicleDataGenerator::nameDataFormatinit()
{
    m_nameList << "Signal.Drivetrain.InternalCombustionEngine.RPM" << "Signal.Chassis.Accelerator.PedalPosition"
         << "Signal.Chassis.Axle.Row1.Wheel.Right.Tire.Pressure" << "Signal.Cabin.Door.Row1.Right.Window.Position";
}

void vehicleDataGenerator::typeDataFormatInit()
{
    m_typeList << "UINT32" << "INT16" << "UINT32" << "INT32";
}

void vehicleDataGenerator::unitDataFormatInit()
{
    m_unitList << "rpm" << "NONE" << "p" << "Pos";
}

void vehicleDataGenerator::init()
{
    m_storeManager_instance = new StoreManager();
    m_storeManager_instance->init();

    nameDataFormatinit();
    typeDataFormatInit();
    unitDataFormatInit();

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(insertData()));

    startTimer();
}

void vehicleDataGenerator::insertData()
{
    CDLData generatedData;

    generatedData.id = to_string(m_count%4);

    generatedData.value = to_string(m_count);

    generatedData.name = m_nameList.at(m_count%4);
    generatedData.type = m_typeList.at(m_count%4);
    generatedData.unit = m_unitList.at(m_count%4);

    (m_count%2==0)?generatedData.valid_state="true":generatedData.valid_state="false";

    string str;
    str.append("201702").append(to_string(m_count));
    generatedData.time_stamp = str;
    m_storeManager_instance->storeData(generatedData.id, generatedData.value, generatedData.name, generatedData.type,
                                       generatedData.unit, generatedData.valid_state, generatedData.time_stamp);
    m_count++;
}

void vehicleDataGenerator::startTimer()
{
    m_timer->start(50);
}


