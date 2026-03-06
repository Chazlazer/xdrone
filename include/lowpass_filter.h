#ifndef LOWPASS_FILTER_H
#define LOWPASS_FILTER_H

#include <wiringPi.h>

#define NOT_SET -1.0f

class LowPassFilter
{
public:
    LowPassFilter(float Tf, float Ts = NOT_SET);
    ~LowPassFilter() = default;

    float operator()(float x);

    float Tf;
    float Ts;

protected:
    unsigned long timestamp_prev;
    float y_prev;
};

#endif