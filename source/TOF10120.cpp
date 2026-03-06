#include "TOF10120.h"
#include <unistd.h>

TOF10120::TOF10120(uint8_t address)
    : _addr(address), _fd(-1) {}

int TOF10120::init(const char *device)
{
    _fd = wiringPiI2CSetupInterface(device, _addr);
    return (_fd >= 0);
}

int TOF10120::get_distance()
{
    if (_fd < 0)
        return -1;

    // Enforce 10Hz max (100ms)
    unsigned long now = millis();
    if (now - _lastRead < 100)
        return -2;   // not ready yet (non-blocking)

    _lastRead = now;

    uint8_t reg = 0x00;
    uint8_t buf[2];

    // Set register pointer
    if (wiringPiI2CRawWrite(_fd, &reg, 1) != 1)
        return -1;

    // Read 2 bytes (no delay here)
    if (wiringPiI2CRawRead(_fd, buf, 2) != 2)
        return -1;

    int distance_mm = (buf[0] << 8) | buf[1];

    if (distance_mm > 2000)
        return -1;

    return distance_mm;
}