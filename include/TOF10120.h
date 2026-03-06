#ifndef TOF10120_H
#define TOF10120_H

#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

class TOF10120
{
public:
    TOF10120(uint8_t address = 0x52);

    int init(const char *device);// initialize I2C
    int get_distance();       // read distance in mm

private:
    int _fd;              // wiringPi file descriptor
    uint8_t _addr;        // I2C address
    int distance_mm = 0;      // last read distance
    unsigned long _lastRead;
};

#endif // TOF10120_H