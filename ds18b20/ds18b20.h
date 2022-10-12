#ifndef DS18B20_h
#define DS18B20_h

#include <stdio.h>
#include <stdlib.h>
#include "onewire.h"

void ds18b20Init(GPIO_Id gpioId);
void broadcastConvert();
float getTemperature(unsigned char* address);
int getTemperatureInt(unsigned char* address);
void printSingleAddress();

#endif