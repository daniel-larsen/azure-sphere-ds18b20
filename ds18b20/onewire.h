#ifndef ONEWIRE_H_   /* Include guard */
#define ONEWIRE_H_

#include <applibs/gpio.h>

int onewireStart(GPIO_Id gpioId);
unsigned char onewireInit(int fd);
unsigned char onewireReadBit(int fd);
unsigned char onewireReadByte(int fd);
void onewireWriteByte(int fd, char data);
unsigned char onewireCRC(unsigned char* addr, unsigned char len);
void onewireClose(int fd);

#endif