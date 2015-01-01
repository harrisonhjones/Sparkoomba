/* 
 * File:   main.cpp
 * Author: Harrison
 *
 * Created on December 31, 2014, 9:38 PM
 */

#include <stdio.h>
#include "sparkoomba.h"
using namespace std;

Sparkoomba SR1;
/*
 * 
 */
int main(int argc, char** argv) {
    printf("Hello World!\n");
    SR1.updateSensors();
    
    printf("Size of short: %\n", sizeof(short));
    printf("Charging: 0x%x (%d) \n", SR1.getChargingState(), SR1.getChargingState());
    printf("Voltage: 0x%x (%d) mV\n", SR1.getVoltage(), SR1.getVoltage());
    printf("Current: 0x%x (%d) mA\n", SR1.getCurrent(), SR1.getCurrent());
    printf("Battery Temp: 0x%x (%d) degrees Celsius\n", SR1.getBatteryTemp(), SR1.getBatteryTemp());
    printf("Battery Charge: 0x%x (%d) mAh\n", SR1.getBatteryCharge(), SR1.getBatteryCharge());
    printf("Battery Capacity: 0x%x (%d) mAh\n", SR1.getBatteryCapacity(), SR1.getBatteryCapacity());
    
    return 0;
}

