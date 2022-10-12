#include <stdbool.h>
#include <time.h>
#include <applibs/log.h>
#include "ds18b20/ds18b20.h"

int main(void)
{
    const struct timespec sleepTime = { .tv_sec = 2, .tv_nsec = 0 };

    ds18b20Init(0); // initinitialize ds18b20 and one wire bus

    while (true) {
        broadcastConvert(); // instruct ds18b20 to convert temperature

        nanosleep(&sleepTime, NULL); // wait at least 750 ms

        // get and print temperature 
        float temp = getTemperature();
        Log_Debug("%.1f\n", temp);

        nanosleep(&sleepTime, NULL);
    }
}
