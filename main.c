#include <stdbool.h>
#include <time.h>
#include <applibs/log.h>
#include "ds18b20/ds18b20.h"

int main(void)
{
    const struct timespec sleepTime = { .tv_sec = 1, .tv_nsec = 0 };

    ds18b20Init(0);

    while (true) {
        broadcastConvert();
        nanosleep(&sleepTime, NULL);
        printSingleAddress();
        nanosleep(&sleepTime, NULL);
        //temp = getTemperature(0);
        //Log_Debug("%.6f", temp);
    }

    return 0;
}
