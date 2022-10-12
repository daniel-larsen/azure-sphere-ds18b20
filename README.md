# Azure Sphere DS18B20 (Work in Progress)

This repository contains the code required to connect a [DS18B20](https://www.maximintegrated.com/en/products/sensors/DS18B20.html) temperature sensor to an [Azure Sphere](https://www.microsoft.com/azure-sphere/) device.

## Installation

1. Copy the ds18b20 folder into your Azure Sphere project. 
2. Add add_subdirectory(ds18b20) to your CMakeLists.txt file. 

```c
#include "ds18b20/ds18b20.h"


```
