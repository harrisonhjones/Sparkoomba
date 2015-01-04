/* 
 * File:   main.cpp
 * Author: Harrison
 *
 * Created on December 31, 2014, 9:38 PM
 */


#include <stdio.h>
#include "sparkoomba.h"
#include "Serial.h"

/*#define RUN_UNIT_TESTS
#define RUN_UNIT_TEST_SETTER
#define RUN_UNIT_TEST_CALLBACK*/

using namespace std;

Sparkoomba SR1;
CSerial serial;
char* lpBuffer = new char[500];

/*
 * 
 */

// Callbacks are expected to return 1 on success or else something else on error
int chargingStateCallback()
{
    switch(SR1.getChargingState())
    {
        case NOT_CHARGING:
            printf("[Callback] - Roomba is NOT CHARGING!\n");
            break;
        case CHARGING_RECOVERY:
            printf("[Callback] - Roomba is in CHARGING RECOVERY!\n");
            break;
        case CHARGING:
            printf("[Callback] - Roomba is CHARGING!\n");
            break;
        case TRICKLE_CHARGING:
            printf("[Callback] - Roomba is TRICKLE CHARGING!\n");
            break;
        case WAITING:
            printf("[Callback] - Roomba is WAITING TO CHARGE!\n");
            break;
        case CHARGING_ERROR:
            printf("[Callback] - Roomba has a CHARGING ERROR!\n");
            break;
        default:
            printf("[Callback] - Roomba has an UNSUPPORTED CHARGING STATE!\n");     
    }
    return 1;
}
int voltageCallback()
{
    printf("The voltage changed!\n");
    return -1;
}
int currentCallback()
{
    printf("The current changed!\n");
    return -1;
}
int batteryTempCallback()
{
    printf("The battery temp changed!\n");
    return -1;
}
int batteryChargeCallback()
{
    printf("The battery charge changed!\n");
    return -1;
}
int batteryCapacityCallback()
{
    printf("The battery capacity changed!\n");
    return -1;
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
    SR1.updateSensors();
    
    //printf("Size of short: %\n", sizeof(short));
    //printf("Charging: 0x%x (%d) \n", SR1.getChargingState(), SR1.getChargingState());
    //printf("Voltage: 0x%x (%d) mV\n", SR1.getVoltage(), SR1.getVoltage());
    //printf("Current: 0x%x (%d) mA\n", SR1.getCurrent(), SR1.getCurrent());
    //printf("Battery Temp: 0x%x (%d) degrees Celsius\n", SR1.getBatteryTemp(), SR1.getBatteryTemp());
    //printf("Battery Charge: 0x%x (%d) mAh\n", SR1.getBatteryCharge(), SR1.getBatteryCharge());
    //printf("Battery Capacity: 0x%x (%d) mAh\n", SR1.getBatteryCapacity(), SR1.getBatteryCapacity());
    
    /*SR1.registerCallback(6,multiply);
    if(SR1.handleCallbacks() == 0)
        printf("Callback success!\n");
    else
        printf("Callback failure!\n");*/
    SR1.registerCallback(CHARGING_STATE,chargingStateCallback);
    //SR1.registerCallback(VOLTAGE,voltageCallback);
    //SR1.registerCallback(CURRENT,currentCallback);
    //SR1.registerCallback(BATTERY_TEMP,batteryTempCallback);
    //SR1.registerCallback(BATTERY_CHARGE,batteryChargeCallback);
    //SR1.registerCallback(BATTERY_CAPACITY,batteryCapacityCallback);
    // Force All Callback to be called
    SR1.handleCallbacks(true);
    SR1.setChargingState(NOT_CHARGING);
    SR1.handleCallbacks();
    SR1.setChargingState(CHARGING_RECOVERY);
    SR1.handleCallbacks();
    SR1.setChargingState(CHARGING);
    SR1.handleCallbacks();
    SR1.setChargingState(TRICKLE_CHARGING);
    SR1.handleCallbacks();
    SR1.setChargingState(WAITING);
    SR1.handleCallbacks();
    SR1.setChargingState(CHARGING_ERROR);
    SR1.handleCallbacks();
    
    /*
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
    
    int callbackErrors = SR1.handleCallbacks();
    if(callbackErrors == 0)
        printf("Callback success!\n");
    else
        printf("Callback failure. Failure num: %d!\n", callbackErrors);
    
    SR1.registerCallback(BATTERY_CAPACITY,NO_CALLBACK);
    
    callbackErrors = SR1.handleCallbacks();
    if(callbackErrors == 0)
        printf("Callback success!\n");
    else
        printf("Callback failure. Failure num: %d!\n", callbackErrors);*/

#ifdef RUN_UNIT_TESTS 
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("===== Running Unit Tests =====\n\n");
    int unitTestFailuresTotal = 0;
    int unitTestFailures = 0;
#ifdef RUN_UNIT_TEST_SETTER
    unitTestFailures = 0;
    printf("===== Running Unit Tests for Setters =====\n");
    printf("Running unit test for setBumpsWheelDrops(i)\n");
    for(int i=0;i<=31;i++)
    {
        SR1.setBumpsWheelDrops(i);
        if(SR1.getBumpsWheelDrops() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setWall(i)\n");
    for(int i=0;i<=1;i++)
    {
        SR1.setWall(i);
        if(SR1.getWall() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setCliffLeft(i)\n");
    for(int i=0;i<=1;i++)
    {
        SR1.setCliffLeft(i);
        if(SR1.getCliffLeft() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setCliffFrontLeft(i)\n");
    for(int i=0;i<=1;i++)
    {
        SR1.setCliffFrontLeft(i);
        if(SR1.getCliffFrontLeft() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setCliffFrontRight(i)\n");
    for(int i=0;i<=1;i++)
    {
        SR1.setCliffFrontRight(i);
        if(SR1.getCliffFrontRight() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setCliffRight(i)\n");
    for(int i=0;i<=1;i++)
    {
        SR1.setCliffRight(i);
        if(SR1.getCliffRight() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setVirtualWall(i)\n");
    for(int i=0;i<=1;i++)
    {
        SR1.setVirtualWall(i);
        if(SR1.getVirtualWall() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setOvercurrents(i)\n");
    for(int i=0;i<=31;i++)
    {
        SR1.setOvercurrents(i);
        if(SR1.getOvercurrents() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setDirtDetectorLeft(i)\n");
    for(int i=0;i<=255;i++)
    {
        SR1.setDirtDetectorLeft(i);
        if(SR1.getDirtDetectorLeft() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setDirtDetectorRight(i)\n");
    for(int i=0;i<=255;i++)
    {
        SR1.setDirtDetectorRight(i);
        if(SR1.getDirtDetectorRight() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setIRByte(i)\n");
    for(int i=0;i<=255;i++)
    {
        SR1.setIRByte(i);
        if(SR1.getIRByte() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setButtons(i)\n");
    for(int i=0;i<=15;i++)
    {
        SR1.setButtons(i);
        if(SR1.getButtons() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setDistance(i)\n");
    for(int i=-32768;i<=32767;i++)
    {
        SR1.setDistance(i);
        if(SR1.getDistance() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setAngle(i)\n");
    for(int i=-32768;i<=32767;i++)
    {
        SR1.setAngle(i);
        if(SR1.getAngle() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setChargingState(i)\n");
    for(int i=0;i<=5;i++)
    {
        SR1.setChargingState(i);
        if(SR1.getChargingState() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setVoltage(i)\n");
    for(int i=0;i<=65535;i++)
    {
        SR1.setVoltage(i);
        if(SR1.getVoltage() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setCurrent(i)\n");
    for(int i=-32768;i<=32767;i++)
    {
        SR1.setCurrent(i);
        if(SR1.getCurrent() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setBatteryTemp(i)\n");
    for(int i=-128;i<=127;i++)
    {
        SR1.setBatteryTemp(i);
        if(SR1.getBatteryTemp() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setBatteryCharge(i)\n");
    for(int i=0;i<=65535;i++)
    {
        SR1.setBatteryCharge(i);
        if(SR1.getBatteryCharge() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("Running unit test for setBatteryCapacity(i)\n");
    for(int i=0;i<=65535;i++)
    {
        SR1.setBatteryCapacity(i);
        if(SR1.getBatteryCapacity() != i)
        {
            unitTestFailures++;
            printf("\t[FAILURE] Unit test failed @ i = %d\n\n",i);
            break;
        }
    }
    printf("SETTER UNIT TEST FAILURES: %d\n\n",unitTestFailures);
    unitTestFailuresTotal += unitTestFailures;
#endif   
#ifdef RUN_UNIT_TEST_CALLBACK
    unitTestFailures = 0;
    printf("===== Running Unit Tests for Callbacks =====\n");
    printf("Running unit test for CHARGING_STATE Callback\n");
    SR1.registerCallback(CHARGING_STATE,chargingStateCallback);
    SR1.registerCallback(VOLTAGE,NO_CALLBACK);
    SR1.registerCallback(CURRENT,NO_CALLBACK);
    SR1.registerCallback(BATTERY_TEMP,NO_CALLBACK);
    SR1.registerCallback(BATTERY_CHARGE,NO_CALLBACK);
    SR1.registerCallback(BATTERY_CAPACITY,NO_CALLBACK);
    SR1.setChargingState(4);
    int callbackErrors = SR1.handleCallbacks();
    if(callbackErrors != 1)
    {
        unitTestFailures++;
        printf("\t[FAILURE] Unit test failed\n");
    }
    printf("CALLBACK UNIT TEST FAILURES: %d\n\n",unitTestFailures);
    unitTestFailuresTotal += unitTestFailures;
#endif 
    printf("TOTAL UNIT TEST FAILURES: %d\n\n",unitTestFailuresTotal);
    printf("===== End Unit Tests =====\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
#endif
    return 0;
}

