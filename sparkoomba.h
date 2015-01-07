/* 
 * File:   sparkoomba.h
 * Author: Harrison
 *
 * Created on December 31, 2014, 9:47 PM
 */

#ifndef SPARKOOMBA_H
#define	SPARKOOMBA_H

#ifdef	__cplusplus
extern "C" {
#endif
#ifdef	__cplusplus
}
#endif

#include "string.h"

#define bumpright (sensorbytes[0] & 0x01)
#define bumpleft  (sensorbytes[0] & 0x02)

#define SERIAL_BEGIN(_baud) Serial1.begin(_baud)
#define SERIAL_SEND(byte) Serial1.write(byte)
#define SERIAL_AVILABLE() Serial1.available()
#define SERIAL_READ() Serial1.read()

// Roomba SCI Op Codes
#define CMD_START 128
#define CMD_BAUD 129
#define CMD_CONTROL 130
#define CMD_SAFE 131
#define CMD_FULL 132
#define CMD_POWER 133
#define CMD_SPOT 134
#define CMD_CLEAN 135
#define CMD_MAX 136
#define CMD_DRIVE 137
#define CMD_MOTORS 138
#define CMD_LEDS 139
#define CMD_SONG 140
#define CMD_PLAY 141
#define CMD_SENSORS 142
#define CMD_FORCE_SEEK_DOCK 143

// Roomba Baud Values
#define ROOMBA_BAUD_300 0
#define ROOMBA_BAUD_600 1
#define ROOMBA_BAUD_1200 2
#define ROOMBA_BAUD_2400 3
#define ROOMBA_BAUD_4800 4
#define ROOMBA_BAUD_9600 5
#define ROOMBA_BAUD_14400 6
#define ROOMBA_BAUD_19200 7
#define ROOMBA_BAUD_28800 8
#define ROOMBA_BAUD_38400 9
#define ROOMBA_BAUD_57600 10
#define ROOMBA_BAUD_115200 11

// Roomba SCI States
#define STATE_SLEEP 0
#define STATE_OFF 1
#define STATE_PASSIVE 2
#define STATE_SAFE 3
#define STATE_FULL 4

// Roomba Charging States
#define NOT_CHARGING 0
#define CHARGING_RECOVERY 1
#define CHARGING 2
#define TRICKLE_CHARGING 3
#define WAITING 4
#define CHARGING_ERROR 5

// Sensor Call Backs
#define CALLBACK_NUM 35
#define CB_BUMPS_AND_WHEEL_DROPS 0
#define CB_WALL 1
#define CB_CLIFF_LEFT 2
#define CB_CLIFF_FRONT_LEFT 3
#define CB_CLIFF_FRONT_RIGHT 4
#define CB_CLIFF_RIGHT 5
#define CB_VIRTUAL_WALL 6
#define CB_OVERCURRENTS 7
#define CB_IR_BYTE 8
#define CB_BUTTONS 9
#define CB_DISTANCE 10
#define CB_ANGLE 11
#define CB_CHARGING_STATE 12
#define CB_VOLTAGE 13
#define CB_CURRENT 14
#define CB_BATTERY_TEMP 15
#define CB_BATTERY_CHARGE 16
#define CB_BATTERY_CAPACITY 17
// Other Callbacks
#define CB_OI_STATE 18
#define CB_BAUD 20
#define CB_START 19
#define CB_CONTROL 21
#define CB_SAFE 22
#define CB_FULL 23
#define CB_POWER 24
#define CB_SPOT 25
#define CB_CLEAN 26
#define CB_MAX 27
#define CB_DRIVE 28
#define CB_MOTORS 29
#define CB_LEDS 30
#define CB_SONG 31
#define CB_PLAY 32
#define CB_SENSORS 33
#define CB_FORCE_SEEK_DOCK 34

#define NO_CALLBACK 0

// LEDs
#define LED_STATUS_RED 4
#define LED_STATUS_GREEN 5
#define LED_SPOT 3
#define LED_CLEAN 2
#define LED_MAX 1
#define LED_DIRT_DETECT 0

// Special motor drive stuff
#define DRIVE_STRAIGHT 32768
#define DRIVE_CLOCKWISE -1
#define DRIVE_CCLOCKWISE 1

#define ALLOWSENSOROVERRIDE
class Sparkoomba
{
public:
    Sparkoomba();
    Sparkoomba(unsigned int _baud, unsigned char _ddPin, bool automaticMode);
    void begin();
    
    // Hardware Level Roomba Functions
    void wakeUp();
    
    // SCI Level Roomba Functions
    void cmdStart();
    bool cmdBaud(unsigned char baud);
    bool cmdControl();
    bool cmdSafe();
    bool cmdFull();
    bool cmdPower();
    bool cmdSpot();
    bool cmdClean();
    bool cmdMax();
    bool cmdDrive(short velocity, short radius);
    bool cmdMotors(bool mainBrush, bool vacuum, bool sideBrush);
    bool cmdLEDs();
    bool cmdSong(unsigned char songNum, unsigned char *songNotes, unsigned char songDuration);
    bool cmdPlay(unsigned char songNum);
    bool cmdSensors();
    bool cmdForceSeekDock();
    
    // Internal State Functions
    // Sensor Getters
    unsigned char getBumpsWheelDrops();
    bool getWall();
    bool getCliffLeft();
    bool getCliffFrontLeft();
    bool getCliffFrontRight();
    bool getCliffRight();
    bool getVirtualWall();
    unsigned char getOvercurrents();
    unsigned char getDirtDetectorLeft();
    unsigned char getDirtDetectorRight();
    unsigned char getIRByte();
    unsigned char getButtons();
    short getDistance();
    short getAngle();
    
    unsigned char getChargingState();
    unsigned short getVoltage();
    short getCurrent();
    char getBatteryTemp();
    unsigned short getBatteryCharge();
    unsigned short getBatteryCapacity();
    
    float getBatteryPercentage();
    
    unsigned char getOIState();
    unsigned int getBaud();
    
    // Callback functions
    int registerCallback(unsigned char sensorType, int (*cbFunc)(void));
    int handleCallbacks(bool forceAllCallbacks);
    int handleCallbacks();
    int handleCallback(unsigned char  callbackNum);
    
    // Object Setters
    void setOIState(unsigned char oiState);
    bool setLEDBit(unsigned char ledId, bool state);
    void setLEDsOff();
    void setPowerLED(unsigned char color, unsigned char intensity);
    
    // Sensor Setters
    #ifdef ALLOWSENSOROVERRIDE
    void setBumpsWheelDrops(unsigned char dBumbsWheelDrops);
    void setWall(bool dWall);
    void setCliffLeft(bool dCliffLeft);
    void setCliffFrontLeft(bool dCliffFrontLeft);
    void setCliffFrontRight(bool dCliffFrontRight);
    void setCliffRight(bool dCliffRight);
    void setVirtualWall(bool dVirtualWall);
    void setOvercurrents(unsigned char dOvercurrents);
    void setDirtDetectorLeft(unsigned char dDirtDetectorLeft);
    void setDirtDetectorRight(unsigned char dDirtDetectorRight);
    void setIRByte(unsigned char dIRByte);
    void setButtons(unsigned char dButtons);
    void setDistance(short dDistance);
    void setAngle(short dAngle);
    void setChargingState(unsigned char dChargingState);
    void setVoltage(unsigned short dVoltage);
    void setCurrent(short dCurrent);
    void setBatteryTemp(char dBatteryTemp);
    void setBatteryCharge(unsigned short dBatteryCharge);
    void setBatteryCapacity(unsigned short dBatteryCapacity);
    #endif
    
private:
    // Physical Roomba Connection Variables
    unsigned char _ddPin;
    unsigned int _baud;
    bool _automaticMode;
    
    unsigned char lastCommand;
    bool lastCommandSuccess;
    
    // Roomba Sensor Variables
    unsigned char currSensorData[26];
    unsigned char prevSensorData[26];
    int (*cbFunc[CALLBACK_NUM])();  // A function pointer to callback functions
    
    // Roomba State Variables
    unsigned char _oiState;
    
    // Command Sending Stuff
    void sendCommand(unsigned char cmd, unsigned char *dataOut, unsigned int dataOutNum);
    
    // Sensor Stuff
    unsigned char getBumpsWheelDrops(bool oldData);
    bool getWall(bool oldData);
    bool getCliffLeft(bool oldData);
    bool getCliffFrontLeft(bool oldData);
    bool getCliffFrontRight(bool oldData);
    bool getCliffRight(bool oldData);
    bool getVirtualWall(bool oldData);
    unsigned char getOvercurrents(bool oldData);
    unsigned char getDirtDetectorLeft(bool oldData);
    unsigned char getDirtDetectorRight(bool oldData);
    unsigned char getIRByte(bool oldData);
    unsigned char getButtons(bool oldData);
    short getDistance(bool oldData);
    short getAngle(bool oldData);
    unsigned char getChargingState(bool oldData);
    unsigned short getVoltage(bool oldData);
    short getCurrent(bool oldData);
    char getBatteryTemp(bool oldData);
    unsigned short getBatteryCharge(bool oldData);
    unsigned short getBatteryCapacity(bool oldData);
    
    // LED Variables
    unsigned char _LEDBits;
    unsigned char _powerLEDColor;
    unsigned char _powerLEDIntensity;
};


#endif	/* SPARKOOMBA_H */

