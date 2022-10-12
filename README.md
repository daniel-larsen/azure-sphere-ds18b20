# Azure Sphere DS18B20 (Work in Progress)

This repository contains the code required to connect a [DS18B20](https://www.maximintegrated.com/en/products/sensors/DS18B20.html) temperature sensor to an [Azure Sphere](https://www.microsoft.com/azure-sphere/) device.

## Installation

1. Copy the ds18b20 folder into your Azure Sphere project. 
2. Add add_subdirectory(ds18b20) to your CMakeLists.txt file. 

```c
#include "ds18b20/ds18b20.h"

ds18b20Init(0); // initinitialize ds18b20 and one wire bus

broadcastConvert(); // instruct ds18b20 to convert temperature

nanosleep(&sleepTime, NULL); // wait at least 750 ms

// get and print temperature 
float temp = getTemperature();
Log_Debug("%.1f C\n", temp);

```
