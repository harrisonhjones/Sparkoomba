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

// Sensor IDs
#define BUMPS_AND_WHEEL_DROPS 0
#define WALL 1
#define CLIFF_LEFT 2
#define CLIFF_FRONT_LEFT 3
#define CLIFF_FRONT_RIGHT 4
#define CLIFF_RIGHT 5
#define VIRTUAL_WALL 6
#define OVERCURRENTS 7
#define IR_BYTE 8
#define BUTTONS 9
#define DISTANCE 10
#define ANGLE 11
#define CHARGING_STATE 12
#define VOLTAGE 13
#define CURRENT 14
#define BATTERY_TEMP 15
#define BATTERY_CHARGE 16
#define BATTERY_CAPACITY 17

#define NO_CALLBACK 0

#define ALLOWSENSOROVERRIDE
class Sparkoomba
{
public:
    Sparkoomba();
    Sparkoomba(int baud, int ddPin);
    Sparkoomba(int ddPin, bool automaticMode);
    Sparkoomba(int baud, int ddPin, bool automaticMode);
    
    // Hardware Level Roomba Functions
    void wakeUp();
    
    // SCI Level Roomba Functions
    void goForward();
    void goBackward();
    void spinLeft();
    void spinRight();
    void stop();
    void updateSensors();
    void playSong();
    void vacuumOn();
    void vacuumOff();
    void goHome();
    void clean();
    void gainControl();
    
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
    
    unsigned char getOIState();
    
    // Callback functions
    int registerCallback(unsigned char sensorType, int (*cbFunc)(void));
    int handleCallbacks(bool forceAllCallbacks);
    int handleCallbacks();
    
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
    int ddPin;
    int baud;
    bool automaticMode;
    
    // Roomba Sensor Variables
    unsigned char currSensorData[26];
    unsigned char prevSensorData[26];
    int (*cbFunc[18])();  // A function pointer to callback functions
    
    // Roomba State Variables
    unsigned char oiState;
    
    // Callback stuff
    int handleCallback(int sensorNum);
    
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
};


#endif	/* SPARKOOMBA_H */

