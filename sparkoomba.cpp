#include "sparkoomba.h"
#include <stdio.h>

#if defined (__cplusplus)
#warning "Compiling as a C++ Application"
#else
#if defined (SPARK)
#warning "Compiling as Spark Firmware"
#error "Not Yet Supported"
#include "application.h"
#else
#if defined(ARDUINO) && ARDUINO >= 100
#warning "Compiling as Arduino Firmware"
#error "Not Yet Supported"
#include "Arduino.h"
#else
#warning "Compiling as old Arduino Firmware"
#error "Not Yet Supported"
#include "WProgram.h"
#endif
#endif
#endif

Sparkoomba::Sparkoomba()
{
    Sparkoomba(57600,0, false);
}
Sparkoomba::Sparkoomba(unsigned int _baud, unsigned char _ddPin)
{
    Sparkoomba(_baud, _ddPin, false);
}
Sparkoomba::Sparkoomba(unsigned char _ddPin, bool automaticMode)
{
    Sparkoomba(57600, _ddPin, automaticMode);
}
Sparkoomba::Sparkoomba(unsigned int _baud, unsigned char _ddPin, bool automaticMode)
{
    this->_baud = _baud;
    this->_ddPin = _ddPin;
    this->_automaticMode = automaticMode;
    this->_oiState = STATE_SLEEP;
    
    #if defined (__cplusplus)
    printf("Sparkoomba Created\nBaud: %d\n_ddPin: %d\nAutomatic Mode: %d\n", _baud, _ddPin, automaticMode);
    #else
    #if defined (SPARK) || defined (ARDUINO))
    #warning "Might be a good place for some debugging"
    #endif
    #endif
}
unsigned char Sparkoomba::getOIState()
{
    return this->_oiState;
}
unsigned int Sparkoomba::getBaud()
{
    return this->_baud;
}
void Sparkoomba::begin()
{
    #if defined (__cplusplus)
    printf("[ROOMBA_ACTION] Begin Called\n");
    #else
    #if defined (SPARK) || defined (ARDUINO))
    SERIAL_BEGIN(this->_baud);
    pinMode(this->_ddPin, OUTPUT);
    digitalWrite(this->_ddPin, HIGH);
    #endif
    #endif
}

void Sparkoomba::wakeUp()
{
    #if defined (__cplusplus)
    printf("[ROOMBA_ACTION] WAKE UP NEO\n");
    #else
    #if defined (SPARK) || defined (ARDUINO))
    // wake up the robot
    digitalWrite(this->_ddPin, LOW);                         // 500ms LOW signal wakes up the robot (docs says 100ms is enough))
    delay(500);
    digitalWrite(this->_ddPin, HIGH);                        // Send it back HIGH once the robot is awake
    delay(2000);
    #endif
    #endif
    this->setOIState(STATE_OFF);
    this->start();
}
void Sparkoomba::setOIState(unsigned char oiState)
{
    this->_oiState = oiState;
    this->handleCallback(CB_OI_STATE);
}
void Sparkoomba::sendCommand(unsigned char cmd, unsigned char *dataOut,  unsigned int dataOutNum)
{
    #if defined (__cplusplus)
    printf("[SEND_COMMAND] %d: [", cmd);
    for(int i = 0; i<dataOutNum; i++)
    {
        if(i == dataOutNum-1)
            printf("%d",dataOut[i]);
        else
            printf("%d,",dataOut[i]);
    }
    printf("]\n");
    #else
    #if defined (SPARK) || defined (ARDUINO))
    // wake up the robot
    SERIAL_SEND(cmd);
    for(int i = 0; i<dataOutNum; i++)
    {
        SERIAL_SEND(dataOut[i]);
    }
    #endif
    #endif
}
void Sparkoomba::start()
{
    // OPCode: 128
    // Data Bytes: 0
    // Description: Starts the SCI. The Start command must be sent before any other SCI commands. This command puts the SCI in passive mode.
    this->sendCommand(CMD_START,0,0);
    this->setOIState(STATE_PASSIVE);
}
bool Sparkoomba::baud(unsigned char baud)
{
    // OPCode: 129
    // Data Bytes: 1 (the baud))
    switch(baud)
    {
        case ROOMBA_BAUD_300:
            this->_baud = 300;
            break;
        case ROOMBA_BAUD_600:
            this->_baud = 600;
            break;
        case ROOMBA_BAUD_1200:
            this->_baud = 1200;
            break;
        case ROOMBA_BAUD_2400:
            this->_baud = 2400;
            break;
        case ROOMBA_BAUD_4800:
            this->_baud = 4800;
            break;
        case ROOMBA_BAUD_9600:
            this->_baud = 9600;
            break;
        case ROOMBA_BAUD_14400:
            this->_baud = 14400;
            break;
        case ROOMBA_BAUD_19200:
            this->_baud = 19200;
            break;
        case ROOMBA_BAUD_28800:
            this->_baud = 28800;
            break;
        case ROOMBA_BAUD_38400:
            this->_baud = 38400;
            break;
        case ROOMBA_BAUD_57600:
            this->_baud = 57600;
            break;
        case ROOMBA_BAUD_115200:
            this->_baud = 115200;
            break;
        default:
            return false;   // Invalid Baud
    }
    unsigned char data[] = {baud};
    this->sendCommand(CMD_BAUD,data,1);
    this->begin();
    this->handleCallback(CB_BAUD);
    return true;
}

void Sparkoomba::goForward()
{
    printf("goForward");
}
void Sparkoomba::goBackward()
{ 
    printf("goBackward");
}
void Sparkoomba::spinLeft()
{
    printf("spinLeft");
}
void Sparkoomba::spinRight()
{
    printf("spinRight");
}
void Sparkoomba::stop()
{
    printf("stop");
}
void Sparkoomba::updateSensors()
{
    // 1. Loads current sensor data into prevSensorData
    memcpy(this->prevSensorData,this->currSensorData,26);
    
    // 2. Updates current sensor data
    // Populate the sensors with arbitrary data
    this->currSensorData[0] = 0x00;    // 0    Bumps and Wheel Drops
    this->currSensorData[1] = 0x00;    //1    Wall
    this->currSensorData[2] = 0x00;    //2    Cliff Left
    this->currSensorData[3] = 0x00;    //3    Cliff Front Left
    this->currSensorData[4] = 0x00;    //4    Cliff Front Right
    this->currSensorData[5] = 0x00;    //5    Cliff Right
    this->currSensorData[6] = 0x00;    //6    Virtual Wall
    this->currSensorData[7] = 0x00;    //7    Overcurrents
    this->currSensorData[8] = 0x00;    //8    Unused
    this->currSensorData[9] = 0x00;    //9    Unused
    this->currSensorData[10] = 0x00;   //10   IR Byte
    this->currSensorData[11] = 0x00;   //11   Buttons
    this->currSensorData[12] = 0x00;   //12   Distance MSB
    this->currSensorData[13] = 0x00;   //13   Distance LSB
    this->currSensorData[14] = 0x00;   //14    Angle MSB
    this->currSensorData[15] = 0x00;   //15   Angle LSB
    this->currSensorData[16] = 0x01;   //16   Charging State
    this->currSensorData[17] = 0x3B;   //17   Voltage MSB  (15.2V)
    this->currSensorData[18] = 0x60;   //18   Voltage LSB
    this->currSensorData[19] = 0xFF;   //19   Current MSB  (-200 mA - discharging)
    this->currSensorData[20] = 0x38;   //20   Current LSB
    this->currSensorData[21] = 0x1D;   //21   Battery Temp (29 degrees C)
    this->currSensorData[22] = 0x09;   //22   Battery Charge MSB   (2,500 mAh)
    this->currSensorData[23] = 0xC4;   //23   Battery Charge LSB
    this->currSensorData[24] = 0x0B;   //24   Battery Capacity MSB (3,000 mAh)
    this->currSensorData[25] = 0xB8;   // 25   Battery Capacity LSB
    
    // Not sure if we should do this each sensor update. It would make sense tho... Make callbacks automatic
    // this->handleCallbacks();
}

void Sparkoomba::playSong()
{
    printf("playSong");
}
void Sparkoomba::vacuumOn()
{
    printf("vacuumOn");
}
void Sparkoomba::vacuumOff()
{
    printf("vacuumOff");
}
void Sparkoomba::goHome()
{
    printf("goHome");
}
void Sparkoomba::clean()
{
    printf("clean");
}
void Sparkoomba::gainControl()
{
    printf("gainControl");
}

// Sensor Stuff
unsigned char Sparkoomba::getBumpsWheelDrops()
{
    return this->getBumpsWheelDrops(false);
}
unsigned char Sparkoomba::getBumpsWheelDrops(bool oldData)
{
    if(oldData)
        return this->prevSensorData[0];
    else
        return this->currSensorData[0];
}
bool Sparkoomba::getWall()
{
    return this->getWall(false);
}
bool Sparkoomba::getWall(bool oldData)
{
    if(oldData)
        return this->prevSensorData[1];
    else
        return this->currSensorData[1];
}
bool Sparkoomba::getCliffLeft()
{
    return this->getCliffLeft(false);
}
bool Sparkoomba::getCliffLeft(bool oldData)
{
    if(oldData)
        return this->prevSensorData[2];
    else
        return this->currSensorData[2];
}
bool Sparkoomba::getCliffFrontLeft()
{
    return this->getCliffFrontLeft(false);
}
bool Sparkoomba::getCliffFrontLeft(bool oldData)
{
    if(oldData)
        return this->prevSensorData[3];
    else
        return this->currSensorData[3];
}
bool Sparkoomba::getCliffFrontRight()
{
    return this->getCliffFrontRight(false);
}
bool Sparkoomba::getCliffFrontRight(bool oldData)
{
    if(oldData)
        return this->prevSensorData[4];
    else
        return this->currSensorData[4];
}
bool Sparkoomba::getCliffRight()
{
    return this->getCliffRight(false);
}
bool Sparkoomba::getCliffRight(bool oldData)
{
    if(oldData)
        return this->prevSensorData[5];
    else
        return this->currSensorData[5];
}
bool Sparkoomba::getVirtualWall()
{
    return this->getVirtualWall(false);
}
bool Sparkoomba::getVirtualWall(bool oldData)
{
    if(oldData)
        return this->prevSensorData[6];
    else
        return this->currSensorData[6];
}
unsigned char Sparkoomba::getOvercurrents()
{
    return this->getOvercurrents(false);
}
unsigned char Sparkoomba::getOvercurrents(bool oldData)
{
    if(oldData)
        return this->prevSensorData[7];
    else
        return this->currSensorData[7];
}
unsigned char Sparkoomba::getDirtDetectorLeft()
{
    return this->getDirtDetectorLeft(false);
}
unsigned char Sparkoomba::getDirtDetectorLeft(bool oldData)
{
    if(oldData)
        return this->prevSensorData[8];
    else
        return this->currSensorData[8];
}
unsigned char Sparkoomba::getDirtDetectorRight()
{
    return this->getDirtDetectorRight(false);
}
unsigned char Sparkoomba::getDirtDetectorRight(bool oldData)
{
    if(oldData)
        return this->prevSensorData[9];
    else
        return this->currSensorData[9];
}
unsigned char Sparkoomba::getIRByte()
{
    return this->getIRByte(false);
}
unsigned char Sparkoomba::getIRByte(bool oldData)
{
    if(oldData)
        return this->prevSensorData[10];
    else
        return this->currSensorData[10];
}
unsigned char Sparkoomba::getButtons()
{
    return this->getButtons(false);
}
unsigned char Sparkoomba::getButtons(bool oldData)
{
    if(oldData)
        return this->prevSensorData[11];
    else
        return this->currSensorData[11];
}
short Sparkoomba::getDistance()
{
    return this->getDistance(false);
}
short Sparkoomba::getDistance(bool oldData)
{
    if(oldData)
        return (this->prevSensorData[12]<<8) + this->prevSensorData[13];
    else
        return (this->currSensorData[12]<<8) + this->currSensorData[13];
}
short Sparkoomba::getAngle()
{
    return this->getAngle(false);
}
short Sparkoomba::getAngle(bool oldData)
{
    if(oldData)
        return (this->prevSensorData[14]<<8) + this->prevSensorData[15];
    else
        return (this->currSensorData[14]<<8) + this->currSensorData[15];
}
unsigned char Sparkoomba::getChargingState()
{
    return this->getChargingState(false);
}
unsigned char Sparkoomba::getChargingState(bool oldData)
{
    if(oldData)
        return this->prevSensorData[16];
    else
        return this->currSensorData[16];
}
unsigned short Sparkoomba::getVoltage()
{
    return this->getVoltage(false);
}
unsigned short Sparkoomba::getVoltage(bool oldData)
{
    if(oldData)
        return (this->prevSensorData[17]<<8) + this->prevSensorData[18];
    else
        return (this->currSensorData[17]<<8) + this->currSensorData[18];
}
short Sparkoomba::getCurrent()
{
    return this->getCurrent(false);
}
short Sparkoomba::getCurrent(bool oldData)
{
    if(oldData)
        return (this->prevSensorData[19]<<8) + this->prevSensorData[20];
    else
        return (this->currSensorData[19]<<8) + this->currSensorData[20];
}
char Sparkoomba::getBatteryTemp()
{
    return this->getBatteryTemp(false);
}
char Sparkoomba::getBatteryTemp(bool oldData)
{
    if(oldData)
        return this->prevSensorData[21];
    else
        return this->currSensorData[21];
}
unsigned short Sparkoomba::getBatteryCharge()
{
    return this->getBatteryCharge(false);
}
unsigned short Sparkoomba::getBatteryCharge(bool oldData)
{
    if(oldData)
        return (this->prevSensorData[22]<<8) + this->prevSensorData[23];
    else
        return (this->currSensorData[22]<<8) + this->currSensorData[23];
}
unsigned short Sparkoomba::getBatteryCapacity()
{
    return this->getBatteryCapacity(false);
}
unsigned short Sparkoomba::getBatteryCapacity(bool oldData)
{
    if(oldData)
        return (this->prevSensorData[24]<<8) + this->prevSensorData[25];
    else
        return (this->currSensorData[24]<<8) + this->currSensorData[25];
}

int Sparkoomba::registerCallback(unsigned char sensorType, int (*cbFunc)(void))
{
    if(sensorType > 25)
    {
        //printf("Invalid sensor type");
        return -1;
    }
    else
    {
        this->cbFunc[sensorType] = cbFunc;
        //printf("Callback function of sensor (%d) registered (%d = %d?)", sensorType, (int) this->cbFunc[sensorType], (int) cbFunc);
    }
}

int Sparkoomba::handleCallback(unsigned char callbackNum)
{
    if (this->cbFunc[callbackNum] == 0)
    {
        //printf("No callback registered for sensor #%d\n",callbackNum);
    }
    else
    {
        int result = (this->cbFunc[callbackNum]());
        if(result != 1)
        {
            //printf("Callback registered for sensor #%d failed with result: %d\n",callbackNum, result);
            return 1;
        }
    }
    return 0;
}

int Sparkoomba::handleCallbacks()
{
    return this->handleCallbacks(false);
}

int Sparkoomba::handleCallbacks(bool forceAllCallbacks)
{
    int errors = 0;
    
    if((getChargingState(true) != getChargingState(false)) || forceAllCallbacks)
        errors += this->handleCallback(CB_CHARGING_STATE);
    if((getVoltage(true) != getVoltage(false)) || forceAllCallbacks)
        errors += this->handleCallback(CB_VOLTAGE);
    if((getCurrent(true) != getCurrent(false)) || forceAllCallbacks)
        errors += this->handleCallback(CB_CURRENT);
    if((getBatteryTemp(true) != getBatteryTemp(false)) || forceAllCallbacks)
        errors += this->handleCallback(CB_BATTERY_TEMP);
    if((getBatteryCharge(true) != getBatteryCharge(false)) || forceAllCallbacks)
        errors += this->handleCallback(CB_BATTERY_CHARGE);
    if((getBatteryCapacity(true) != getBatteryCapacity(false)) || forceAllCallbacks)
        errors += this->handleCallback(CB_BATTERY_CAPACITY);
    //printf("Num errors: %d\n",errors);
    return errors;
}

    #ifdef ALLOWSENSOROVERRIDE
    #warning "Sensor Override Allowed!"
//oid Sparkoomba::
    void Sparkoomba::setBumpsWheelDrops(unsigned char dBumbsWheelDrops)
    {
        this->currSensorData[0] = dBumbsWheelDrops;
    }
    void Sparkoomba::setWall(bool dWall)
    {
        this->currSensorData[1] = dWall;
    }
    void Sparkoomba::setCliffLeft(bool dCliffLeft)
    {
        this->currSensorData[2] = dCliffLeft;
    }
    void Sparkoomba::setCliffFrontLeft(bool dCliffFrontLeft)
    {
        this->currSensorData[3] = dCliffFrontLeft;
    }
    void Sparkoomba::setCliffFrontRight(bool dCliffFrontRight)
    {
        this->currSensorData[4] = dCliffFrontRight;
    }
    void Sparkoomba::setCliffRight(bool dCliffRight)
    {
        this->currSensorData[5] = dCliffRight;
    }
    void Sparkoomba::setVirtualWall(bool dVirtualWall)
    {
        this->currSensorData[6] = dVirtualWall;
    }
    void Sparkoomba::setOvercurrents(unsigned char dOvercurrents)
    {
        this->currSensorData[7] = dOvercurrents;
    }
    void Sparkoomba::setDirtDetectorLeft(unsigned char dDirtDetectorLeft)
    {
        this->currSensorData[8] = dDirtDetectorLeft;
    }
    void Sparkoomba::setDirtDetectorRight(unsigned char dDirtDetectorRight)
    {
        this->currSensorData[9] = dDirtDetectorRight;
    }
    void Sparkoomba::setIRByte(unsigned char dIRByte)
    {
        this->currSensorData[10] = dIRByte;
    }
    void Sparkoomba::setButtons(unsigned char dButtons)
    {
        this->currSensorData[11] = dButtons;
    }
    void Sparkoomba::setDistance(short dDistance)
    {
        this->currSensorData[12] = dDistance>>8;
        this->currSensorData[13] = dDistance;
    }
    void Sparkoomba::setAngle(short dAngle)
    {
        this->currSensorData[14] = dAngle>>8;
        this->currSensorData[15] = dAngle;
    }
    void Sparkoomba::setChargingState(unsigned char dChargingState){
        this->currSensorData[16] = dChargingState;
    }
    void Sparkoomba::setVoltage(unsigned short dVoltage){
        this->currSensorData[17] = dVoltage>>8;
        this->currSensorData[18] = dVoltage;
    }
    void Sparkoomba::setCurrent(short dCurrent){
        this->currSensorData[19] = dCurrent>>8;
        this->currSensorData[20] = dCurrent;
    }
    void Sparkoomba::setBatteryTemp(char dBatteryTemp){
        this->currSensorData[21] = dBatteryTemp;
    }
    void Sparkoomba::setBatteryCharge(unsigned short dBatteryCharge){
        this->currSensorData[22] = dBatteryCharge>>8;
        this->currSensorData[23] = dBatteryCharge;
    }
    void Sparkoomba::setBatteryCapacity(unsigned short dBatteryCapacity){
        this->currSensorData[24] = dBatteryCapacity>>8;
        this->currSensorData[25] = dBatteryCapacity;
    }
    #endif