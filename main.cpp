/* 
 * File:   main.cpp
 * Author: Harrison
 *
 * Created on December 31, 2014, 9:38 PM
 */

#include <stdio.h>
#include "sparkoomba.h"
#include "Serial.h"

using namespace std;

Sparkoomba SR1;
CSerial serial;
char* lpBuffer = new char[500];

/*
 * 
 */

int multiply()
{
    printf("3 * 3 = 9!\n");
    return 1;
}


int main(int argc, char** argv) {
    // Connect the serial object
    /*if (serial.Open(4, 9600))
    {
        printf("Serial port opened successfully!");
        
        while(serial.ReadDataWaiting() == 0)
        {}
        Sleep(1000);
        while(serial.ReadDataWaiting())
        {
            int nBytesRead = serial.ReadData(lpBuffer, 500);

            printf("Data: [%d]",nBytesRead);
            printf(lpBuffer);
            printf("\n");
        }
        
        
        serial.Close();
    }
    else
        printf("Unable to open serial port!");*/
    
    printf("Hello World!\n");
    SR1.updateSensors();
    
    printf("Size of short: %\n", sizeof(short));
    printf("Charging: 0x%x (%d) \n", SR1.getChargingState(), SR1.getChargingState());
    printf("Voltage: 0x%x (%d) mV\n", SR1.getVoltage(), SR1.getVoltage());
    printf("Current: 0x%x (%d) mA\n", SR1.getCurrent(), SR1.getCurrent());
    printf("Battery Temp: 0x%x (%d) degrees Celsius\n", SR1.getBatteryTemp(), SR1.getBatteryTemp());
    printf("Battery Charge: 0x%x (%d) mAh\n", SR1.getBatteryCharge(), SR1.getBatteryCharge());
    printf("Battery Capacity: 0x%x (%d) mAh\n", SR1.getBatteryCapacity(), SR1.getBatteryCapacity());
    
    SR1.registerCallback(6,multiply);
    if(SR1.handleCallbacks() == 0)
        printf("Callback success!\n");
    else
        printf("Callback failure!\n");
    return 0;
}

