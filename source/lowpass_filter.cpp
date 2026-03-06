#include "lowpass_filter.h"

LowPassFilter::LowPassFilter(float time_constant, float sampling_time)
    : Tf(time_constant),
      Ts(sampling_time),
      y_prev(0.0f)
{
    timestamp_prev = micros();   // wiringPi timing function
}

float LowPassFilter::operator()(float x)
{
    float dt = Ts;

    // If Ts not fixed → use measured time
    if (Ts == NOT_SET)
    {
        unsigned long timestamp = micros();
        dt = (timestamp - timestamp_prev) * 1e-6f;

        if (dt < 0.0f)
            dt = 1e-3f;

        else if (dt > 0.3f) {
            y_prev = x;
            timestamp_prev = timestamp;
            return x;
        }

        timestamp_prev = timestamp;
    }

    // First-order low pass filter
    float alpha = Tf / (Tf + dt);
    float y = alpha * y_prev + (1.0f - alpha) * x;

    y_prev = y;
    return y;
}