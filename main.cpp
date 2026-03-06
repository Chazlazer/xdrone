#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdint.h>
#include "TOF10120.h"
#include "lowpass_filter.h"

#define READ_INTERVAL_MS 100   // 10 Hz max

int SensorRead(int fd);
TOF10120 sensor(0x52);
LowPassFilter lpf = LowPassFilter(0.1f); // 0.5s time constant
int main()
{
    wiringPiSetup();

    if (!sensor.init("/dev/i2c-0")) {
        std::cout << "Failed to connect to TOF10120" << std::endl;
        return -1;
    }

    pinMode(0, OUTPUT);

    unsigned long lastRead = 0;

    while(true)
    {
        unsigned long now = millis();

        // Only read every 100ms (non-blocking)
        if (now - lastRead >= READ_INTERVAL_MS)
        {
            lastRead = now;
            int distance = sensor.get_distance();
            if (distance >= 0)
            {
                std::cout << "Distance: " << distance << " mm" << std::endl;

                if (distance < 100)
                    digitalWrite(0, HIGH);
                else
                    digitalWrite(0, LOW);
            }
        }

        // Other code can run here (RF, control, etc.)
        usleep(1); // small sleep to reduce CPU usage
    }

    return 0;
}