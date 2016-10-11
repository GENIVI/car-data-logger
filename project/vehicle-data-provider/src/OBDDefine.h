//#ifndef OBDDEFINE
//#define OBDDEFINE

//#include <QObject>
//#include <QVector>

//namespace OBD {

//#define STX 					0x02
//#define CR						0x0D
//#define ESCAPE                  0x7D
//#define ESC_COMPLEMENT_VALUE    0x20

//#define TARGET_POS          0x01
//#define SOURCE_POS          0x02
//#define MAIN_ID_POS         0x03
//#define SUB_ID_POS          0x04
//#define LENGTH_POS          0x05
//#define DATA_POS            0x07

//#define FLOAT_SIZE          sizeof(float)

//enum Target
//{
//    eTARGET_UART            = 0x10,
//    eTARGET_USB             = 0x11,
//    eTARGET_BT              = 0x12,
//    eTARGET_WIFI            = 0x13,

//    eTARGET_EXTERNAL_MEORY  = 0x81,
//    eTARGET_DIAGNOSIS       = 0x90,
//    eTARGET_FIRMWARE        = 0xA0,
//    eTARGET_BYPASS          = 0xC0,
//};

//enum Source
//{
//    eSOURCE_UART            = 0x10,
//    eSOURCE_USB             = 0x11,
//    eSOURCE_BT              = 0x12,
//    eSOURCE_WIFI            = 0x13,

//    eSOURCE_EXTERNAL_MEORY  = 0x81,
//    eSOURCE_DIAGNOSIS       = 0x90,
//    eSOURCE_FIRMWARE        = 0xA0,
//    eSOURCE_BYPASS          = 0xC0,
//};

//enum MainID
//{
//    ID_FIRMWARE_BLUETOOTH   = 0x70,
//    ID_REQUEST_SENSOR_DATA  = 0x20
//};

//enum SubID
//{
//    // ID_FIRMWARE_BLUETOOTH
//    SID_FIRMWARE_BLUETOOTH_SW_PIN_CODE      = 0x50,

//    // ID_REQUEST_SENSOR_DATA
//    SID_REQUEST_SENSOR_DATA_ALL             = 0x10,
//    SID_REQUEST_SENSOR_DATA_SELECTED_ITEM   = 0x20, // request get selected item
//    SID_REQUEST_SENSOR_DATA_SELECT_ITEM     = 0x21, // request set selecet item
//    SID_REQUEST_SENSOR_DATA_ONCE            = 0x30,
//    SID_REQUEST_SENSOR_DATA_BROADCASTING    = 0x31,

//};

//enum SensorID
//{
//    //Sensor ID
//    SENSOR_ID_CLV		= 0x00000400,		//Calculated Load Value
//    SENSOR_ID_ECT		= 0x00000500,		//Engine Coolant Temperature
//    SENSOR_ID_RPM 		= 0x00000C00,
//    SENSOR_ID_SPEED     = 0x00000D00,
//    SENSOR_ID_IAT		= 0x00000F00,		//Intake Air Temperature
//    SENSOR_ID_AFR_MAF	= 0x00001000,		//Air Flow Rate From MAF Sensor
//    SENSOR_ID_DWM		= 0x00002100,		//Distance While Mil
//    SENSOR_ID_FLI		= 0x00002F00,		//Fuel Level Input
//    SENSOR_ID_CMV		= 0x00004200,		//Control Module Voltage
//};

//enum SensorIDIndex
//{
//    //Sensor ID Index
//    SENSOR_IDX_CLV,
//    SENSOR_IDX_ECT,
//    SENSOR_IDX_RPM,
//    SENSOR_IDX_SPEED,
//    SENSOR_IDX_IAT,
//    SENSOR_IDX_AFR_MAF,
//    SENSOR_IDX_DWM,
//    SENSOR_IDX_FLI,
//    SENSOR_IDX_CMV,
//};

//enum DataType
//{
//    TYPEFLOAT = 0x95,
//};

//typedef QVector<float> SNSData;

//}

//#endif // OBDDEFINE

