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
    Sparkoomba(57600,0);
}
Sparkoomba::Sparkoomba(int baud, int ddPin)
{
    this->baud = baud;
    this->ddPin = ddPin;
    printf("Sparkoomba Created\nBaud: %d\nddPin: %d", baud, ddPin);
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
    // Populate the sensors with arbitrary data
    this->sensorbytes[0] = 0x00;    // 0    Bumps and Wheel Drops
    this->sensorbytes[1] = 0x00;    //1    Wall
    this->sensorbytes[2] = 0x00;    //2    Cliff Left
    this->sensorbytes[3] = 0x00;    //3    Cliff Front Left
    this->sensorbytes[4] = 0x00;    //4    Cliff Front Right
    this->sensorbytes[5] = 0x00;    //5    Cliff Right
    this->sensorbytes[6] = 0x00;    //6    Virtual Wall
    this->sensorbytes[7] = 0x00;    //7    Overcurrents
    this->sensorbytes[8] = 0x00;    //8    Unused
    this->sensorbytes[9] = 0x00;    //9    Unused
    this->sensorbytes[10] = 0x00;   //10   IR Byte
    this->sensorbytes[11] = 0x00;   //11   Buttons
    this->sensorbytes[12] = 0x00;   //12   Distance MSB
    this->sensorbytes[13] = 0x00;   //13   Distance LSB
    this->sensorbytes[14] = 0x00;   //14    Angle MSB
    this->sensorbytes[15] = 0x00;   //15   Angle LSB
    this->sensorbytes[16] = 0x01;   //16   Charging State
    this->sensorbytes[17] = 0x3B;   //17   Voltage MSB  (15.2V)
    this->sensorbytes[18] = 0x60;   //18   Voltage LSB
    this->sensorbytes[19] = 0xFF;   //19   Current MSB  (-200 mA - discharging)
    this->sensorbytes[20] = 0x38;   //20   Current LSB
    this->sensorbytes[21] = 0x1D;   //21   Battery Temp (29 degrees C)
    this->sensorbytes[22] = 0x09;   //22   Battery Charge MSB   (2,500 mAh)
    this->sensorbytes[23] = 0xC4;   //23   Battery Charge LSB
    this->sensorbytes[24] = 0x0B;   //24   Battery Capacity MSB (3,000 mAh)
    this->sensorbytes[25] = 0xB8;   // 25   Battery Capacity LSB
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
unsigned char Sparkoomba::getChargingState()
{
    return this->sensorbytes[16];
}

unsigned short Sparkoomba::getVoltage()
{
    return (this->sensorbytes[17]<<8) + this->sensorbytes[18];
}
short Sparkoomba::getCurrent()
{
    return (this->sensorbytes[19]<<8) + this->sensorbytes[20];
}
char Sparkoomba::getBatteryTemp()
{
    return this->sensorbytes[21];
}
unsigned short Sparkoomba::getBatteryCharge()
{
    return (this->sensorbytes[22]<<8) + this->sensorbytes[23];
}
unsigned short Sparkoomba::getBatteryCapacity()
{
    return (this->sensorbytes[24]<<8) + this->sensorbytes[25];
}

int Sparkoomba::registerCallback(unsigned char sensorType, int (*cbFunc)(void))
{
    if(sensorType > 25)
    {
        printf("Invalid sensor type");
        return -1;
    }
    else
    {
        this->cbFunc[sensorType] = cbFunc;
        printf("Callback function of sensor (%d) registered (%d = %d?)", sensorType, (int) this->cbFunc[sensorType], (int) cbFunc);
    }
}

int Sparkoomba::handleCallbacks()
{
    int errors = 0;
    for(int i = 0; i<26; i++)
    {
        if (this->cbFunc[i] == 0)
        {
            printf("No callback registered for sensor #%d\n",i);
        }
        else
        {
            int result = (this->cbFunc[i]());
            if(result != 1)
            {
                printf("Callback registered for sensor #%d failed with result: %d\n",i, result);
                errors++;
            }
        }
    }
    return errors;
}

    #ifdef ALLOWSENSOROVERRIDE
    #warning "Sensor Override Allowed!"
    void Sparkoomba::setChargingState(unsigned char dChargingState){
        this->sensorbytes[16] = dChargingState;
    }
    void Sparkoomba::setVoltage(unsigned short dVoltage){
        this->sensorbytes[17] = dVoltage>>8;
        this->sensorbytes[18] = dVoltage;
    }
    void Sparkoomba::setCurrent(short dCurrent){
        this->sensorbytes[19] = dCurrent>>8;
        this->sensorbytes[20] = dCurrent;
    }
    void Sparkoomba::setBatteryTemp(char dBatteryTemp){
        this->sensorbytes[21] = dBatteryTemp;
    }
    void Sparkoomba::setBatteryCharge(unsigned short dBatteryCharge){
        this->sensorbytes[22] = dBatteryCharge>>8;
        this->sensorbytes[23] = dBatteryCharge;
    }
    void Sparkoomba::setBatteryCapacity(unsigned short dBatteryCapacity){
        this->sensorbytes[24] = dBatteryCapacity>>8;
        this->sensorbytes[25] = dBatteryCapacity;
    }
    #endif