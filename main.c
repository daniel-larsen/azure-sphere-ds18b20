#include <stdbool.h>
#include <time.h>
#include <applibs/log.h>
#include "ds18b20/ds18b20.h"

int sensor = -1;

int main(void)
{
    const struct timespec sleepTime = { .tv_sec = 2, .tv_nsec = 0 };

    sensor = ds18b20Init(0); // initinitialize ds18b20 and one wire bus on GPIO0

    while (true) {
        ds18b20Convert(sensor); // instruct ds18b20 to convert temperature

        nanosleep(&sleepTime, NULL); // wait at least 750 ms

        // get and print temperature 
        float temp = ds18b20GetTemperature(sensor);
        if (temp != INVALID_TEMPERATURE) {
            Log_Debug("%.1f C\n", temp);
        }

        nanosleep(&sleepTime, NULL);
    }
}
