#include "onewire.h"
#include "ds18b20.h"
#include <applibs/log.h>

/*
  send message to every sensor on the bus to take a reading
*/
void broadcastConvert() {
  //broadcast that temp conversions should begin, all at once so saves time
  onewireInit();
  onewireWriteByte(0xCC);
  onewireWriteByte(0x44);

  while (1) {
    if (onewireReadBit())
      break;
  }
}

/*
  retrieve temperatures from sensors
*/
float getTemperature() {
  unsigned char scratchPad[9] = { 0,0,0,0,0,0,0,0,0 };

  onewireInit();
  unsigned char address[8] = { 0,0,0,0,0,0,0,0 };
  onewireWriteByte(0x33);
  for (uint8_t i = 0; i < 8; i++) {
    address[i] = onewireReadByte();
  }

  unsigned char crc = onewireCRC(address, 7);

  onewireInit();
  onewireWriteByte(0x55);
  for (uint8_t i = 0; i < 8; i++) {
      onewireWriteByte(address[i]);
  }
  onewireWriteByte(0xBE);

  for (uint8_t i = 0; i < 2; i++) {
    scratchPad[i] = onewireReadByte();
  }
  float temperature = ((scratchPad[1] * 256) + scratchPad[0])*0.0625;

  return temperature;
}

int getTemperatureInt(unsigned char* address) {
  //get temperature from the device with address address
  int temperature;
  unsigned char scratchPad[9] = {0,0,0,0,0,0,0,0,0};

  onewireInit();
  onewireWriteByte(0x55);
  unsigned char i;
  for (i = 0; i < 8; i++)
    onewireWriteByte(address[i]);
  onewireWriteByte(0xBE);

  for (i = 0; i < 2; i++) {
    scratchPad[i] = onewireReadByte();
  }
  onewireInit();
  temperature = ((scratchPad[1] * 256) + scratchPad[0]);

  return temperature;
}

/*
  retrieve address of sensor and print to terminal
*/
void printSingleAddress() {
  onewireInit();
  //attach one sensor to port 25 and this will print out it's address
  unsigned char address[8]= {0,0,0,0,0,0,0,0};
  onewireWriteByte(0x33);
  unsigned char i;
  for (i = 0; i<8; i++)
    address[i] = onewireReadByte();
  for (i = 0; i<8; i++)
    Log_Debug("0x%x,",address[i]);
  
  //check crc
  unsigned char crc = onewireCRC(address, 7);
  Log_Debug("crc = %x \r\n",crc);
}

void ds18b20Init(GPIO_Id gpioId) {
    onewireStart(gpioId);
}