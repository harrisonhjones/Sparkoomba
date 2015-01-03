/* 
 * File:   main.cpp
 * Author: Harrison
 *
 * Created on December 31, 2014, 9:38 PM
 */


#include <stdio.h>
#include "sparkoomba.h"
#include "Serial.h"

#define RUN_UNIT_TESTS

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
    
    /*SR1.registerCallback(6,multiply);
    if(SR1.handleCallbacks() == 0)
        printf("Callback success!\n");
    else
        printf("Callback failure!\n");*/
    
    SR1.setChargingState(4);
    SR1.setVoltage(17531);
    SR1.setCurrent(-55);
    SR1.setBatteryTemp(-4);
    SR1.setBatteryCharge(1000);
    SR1.setBatteryCapacity(5000);
    
    printf("Charging: 0x%x (%d) \n", SR1.getChargingState(), SR1.getChargingState());
    printf("Voltage: 0x%x (%d) mV\n", SR1.getVoltage(), SR1.getVoltage());
    printf("Current: 0x%x (%d) mA\n", SR1.getCurrent(), SR1.getCurrent());
    printf("Battery Temp: 0x%x (%d) degrees Celsius\n", SR1.getBatteryTemp(), SR1.getBatteryTemp());
    printf("Battery Charge: 0x%x (%d) mAh\n", SR1.getBatteryCharge(), SR1.getBatteryCharge());
    printf("Battery Capacity: 0x%x (%d) mAh\n", SR1.getBatteryCapacity(), SR1.getBatteryCapacity());
    
#ifdef RUN_UNIT_TESTS
    printf("Running unit test for setChargingState(i)\n");
    for(int i=0;i<6;i++)
    {
        SR1.setChargingState(i);
        if(SR1.getChargingState() != i)
        {
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setVoltage(i)\n");
    for(int i=0;i<65535;i++)
    {
        SR1.setVoltage(i);
        if(SR1.getVoltage() != i)
        {
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setCurrent(i)\n");
    for(int i=-32768;i<32767;i++)
    {
        SR1.setCurrent(i);
        if(SR1.getCurrent() != i)
        {
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setBatteryTemp(i)\n");
    for(int i=-128;i<127;i++)
    {
        SR1.setBatteryTemp(i);
        if(SR1.getBatteryTemp() != i)
        {
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setBatteryCharge(i)\n");
    for(int i=0;i<65535;i++)
    {
        SR1.setBatteryCharge(i);
        if(SR1.getBatteryCharge() != i)
        {
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setBatteryCapacity(i)\n");
    for(int i=0;i<65535;i++)
    {
        SR1.setBatteryCapacity(i);
        if(SR1.getBatteryCapacity() != i)
        {
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
#endif
    return 0;
}

