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

#define bumpright (sensorbytes[0] & 0x01)
#define bumpleft  (sensorbytes[0] & 0x02)

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

class Sparkoomba
{
public:
    Sparkoomba();
    Sparkoomba(int baud, int ddPin);
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
    
    // Sensor Stuff
    int getChargingState();
    short getVoltage();
    short getCurrent();
    int getBatteryTemp();
    short getBatteryCharge();
    short getBatteryCapacity();
    int registerCallback(unsigned char sensorType, int (*cbFunc)(void));
    int handleCallbacks();
    
private:
    int ddPin;
    int baud;
    unsigned char sensorbytes[26];
    int (*cbFunc[26])();  // A function pointer to callback functions
};


#endif	/* SPARKOOMBA_H */

