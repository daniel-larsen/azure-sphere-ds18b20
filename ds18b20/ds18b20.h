#ifndef DS18B20_h
#define DS18B20_h

#include <stdio.h>
#include <stdlib.h>
#include "onewire.h"

int ds18b20Init(GPIO_Id gpioId);
void ds18b20Convert(int fd);
float ds18b20GetTemperature(int fd);
float ds18b20GetTemperatureAddress(int fd, unsigned char* address);
void ds18b20PrintSingleAddress(int fd);
void ds18b20Close(int fd);

#endif