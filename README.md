# Azure Sphere DS18B20 (Work in Progress)

This repository contains the code required to connect a [DS18B20](https://www.maximintegrated.com/en/products/sensors/DS18B20.html) temperature sensor to an [Azure Sphere](https://www.microsoft.com/azure-sphere/) device.

## Installation

1. Copy the *ds18b20* folder into your Azure Sphere project. 
2. Add *add_subdirectory(ds18b20)* to your CMakeLists.txt file. 

```c
#include "ds18b20/ds18b20.h"

int sensor = -1;

int main(void)
{
    sensor = ds18b20Init(0); // initinitialize ds18b20 and one wire bus on GPIO0

    ds18b20Convert(sensor); // instruct ds18b20 to convert temperature

    // wait at least 750 ms

    // get and print temperature
    float temp = ds18b20GetTemperature(sensor);
    Log_Debug("%.1f C\n", temp);
}

```

### Credit
This project was adapted from libraries found at https://github.com/simonbarker/pic-libraries.
