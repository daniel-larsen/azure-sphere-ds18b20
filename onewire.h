#ifndef ONEWIRE_H_   /* Include guard */
#define ONEWIRE_H_

#include <applibs/gpio.h>

void onewireStart(GPIO_Id gpioId);
unsigned char onewireInit();
unsigned char onewireReadBit();
unsigned char onewireReadByte();
void onewireWriteByte(char data);
unsigned char onewireCRC(unsigned char* addr, unsigned char len);

#endif