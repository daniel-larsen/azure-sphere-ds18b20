#include "onewire.h"
#include <stdbool.h>
#include <time.h>
#include <applibs/log.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int onewireStart(GPIO_Id gpioId) {
    int fd = GPIO_OpenAsOutput(gpioId, GPIO_OutputMode_OpenDrain, GPIO_Value_High);
    if (fd < 0) {
        Log_Debug(
            "Error opening GPIO: %s (%d). Check that app_manifest.json includes the GPIO used.\n",
            strerror(errno), errno);
    }
    return fd;
}

void onewirePin(int fd, bool level) {
    if (level) {
        GPIO_SetValue(fd, GPIO_Value_High);
    }
    else {
        GPIO_SetValue(fd, GPIO_Value_Low);
    }
}

bool onewireRead(int fd) {
    GPIO_Value_Type result;
    GPIO_GetValue(fd, &result);
    if (result == GPIO_Value_High) {
        return true;
    }
    else {
        return false;
    }
}

void delay_us(long usec) {
    struct timespec delay, remaining;
    delay.tv_sec = 0;
    delay.tv_nsec = usec * 1000;
    remaining.tv_sec = 0;
    remaining.tv_nsec = 0;

    do {
        nanosleep(&delay, &remaining);
    } while (remaining.tv_nsec > 0);
}

void onewireWriteBit(int fd, int b) {
    b = b & 0x01;
    if (b) {
        // Write '1' bit
        onewirePin(fd, false);
        onewirePin(fd, true);
        delay_us(10);
    }
    else {
        // Write '0' bit
        onewirePin(fd, false);
        delay_us(10);
        onewirePin(fd, true);
    }
}

unsigned char onewireReadBit(int fd) {
    unsigned char result;

    onewirePin(fd, false);
    onewirePin(fd,true);
    result = onewireRead(fd);
    delay_us(10);
    return result;

}

unsigned char onewireInit(int fd) {
    onewirePin(fd, false);
    delay_us(480);
    onewirePin(fd, true);
    delay_us(30);
    if (onewireRead(fd) == 0) {
        delay_us(60);
        return 1;
    }
    return 0;
}

unsigned char onewireReadByte(int fd) {
    unsigned char result = 0;

    for (unsigned char loop = 0; loop < 8; loop++) {
        // shift the result to get it ready for the next bit
        result >>= 1;

        // if result is one, then set MS bit
        if (onewireReadBit(fd))
            result |= 0x80;
    }
    return result;
}

void onewireWriteByte(int fd, char data) {
    // Loop to write each bit in the byte, LS-bit first
    for (unsigned char loop = 0; loop < 8; loop++) {
        onewireWriteBit(fd, data & 0x01);

        // shift the data byte for the next bit
        data >>= 1;
    }
}

unsigned char onewireCRC(unsigned char* addr, unsigned char len) {
    unsigned char i, j;
    unsigned char crc = 0;

    for (i = 0; i < len; i++) {
        unsigned char inbyte = addr[i];
        for (j = 0; j < 8; j++) {
            unsigned char mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }

    return crc;
}

void onewireClose(int fd) {
    close(fd);
}