#include "onewire.h"
#include "ds18b20.h"
#include <applibs/log.h>

/*
  send message to every sensor on the bus to take a reading
*/
void ds18b20Convert(int fd) {
  //broadcast that temp conversions should begin, all at once so saves time
  onewireInit(fd);
  onewireWriteByte(fd, 0xCC);
  onewireWriteByte(fd, 0x44);

  while (1) {
    if (onewireReadBit(fd))
      break;
  }
}

/*
  retrieve temperatures from sensors
*/
float ds18b20GetTemperature(int fd) {
  unsigned char scratchPad[9] = { 0,0,0,0,0,0,0,0,0 };

  onewireInit(fd);
  onewireWriteByte(fd, 0xCC);
  onewireWriteByte(fd, 0xBE);

  for (uint8_t i = 0; i < 2; i++) {
    scratchPad[i] = onewireReadByte(fd);
  }

  float temperature = ((scratchPad[1] * 256) + scratchPad[0])*0.0625;

  return temperature;
}

float ds18b20GetTemperatureAddress(int fd, unsigned char* address) {
    //get temperature from the device with address address
    float temperature;
    unsigned char scratchPad[9] = { 0,0,0,0,0,0,0,0,0 };

    onewireInit(fd);
    onewireWriteByte(fd, 0x55);
    unsigned char i;
    for (i = 0; i < 8; i++)
        onewireWriteByte(fd, address[i]);
    onewireWriteByte(fd, 0xBE);

    for (i = 0; i < 2; i++) {
        scratchPad[i] = onewireReadByte(fd);
    }
    temperature = ((scratchPad[1] * 256) + scratchPad[0]) * 0.0625;

    return temperature;
}

/*
  retrieve address of sensor and print to terminal
*/
void ds18b20PrintSingleAddress(int fd) {
  onewireInit(fd);
  //attach one sensor to port 25 and this will print out it's address
  unsigned char address[8]= {0,0,0,0,0,0,0,0};
  onewireWriteByte(fd, 0x33);
  unsigned char i;
  for (i = 0; i<8; i++)
    address[i] = onewireReadByte(fd);
  for (i = 0; i<8; i++)
    Log_Debug("0x%x,",address[i]);
  
  //check crc
  unsigned char crc = onewireCRC(address, 7);
  Log_Debug("crc = %x \r\n",crc);
}

int ds18b20Init(GPIO_Id gpioId) {
    return onewireStart(gpioId);
}

void ds18b20Close(int fd) {
    onewireClose(fd);
}