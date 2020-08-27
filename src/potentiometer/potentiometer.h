#pragma once

#include "../control/control.h"

#include <Arduino.h>

namespace controlino
{

struct Potentiometer : Control
{
    struct Noise
    {
        // encapsulating all configurable parameters
        // that are dependent on the setup itself

        Noise() : Noise(0.8, 1.1, 2)
        {}

        Noise(float down, float up, unsigned char fluctuation) :
            down(down),
            up(up),
            fluctuation(fluctuation)
        {}

        float down; // a multiplier for lowering 'min'
        float up; // a multiplier for uppering 'max'
        unsigned char fluctuation; // how much noise is acceptible
    };

    enum class Event : char
    {
        None, // nothing has happened

        Changed,
    };

    Potentiometer(Pin pin, const Noise & noise = {});
    Potentiometer(Pin pin, int min = -1, int max = -1, const Noise & noise = {});
    Potentiometer(Multiplexer & multiplexer, Pin pin, const Noise & noise = {});
    Potentiometer(Multiplexer & multiplexer, Pin pin, int min = -1, int max = -1, const Noise & noise = {});

    Event check();
    int read();

private:
    int _min;
    int _max;
    Noise _noise;
    int _previous;
};

} // controlino
