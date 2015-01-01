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
private:
    int ddPin;
    int baud;
    unsigned char sensorbytes[26];
};


#endif	/* SPARKOOMBA_H */

