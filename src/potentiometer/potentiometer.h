#pragma once

#include "../control/control.h"

#include <Arduino.h>

namespace controlino
{

struct Potentiometer : Control
{
    enum class Event : char
    {
        None, // nothing has happened

        Changed,
    };

    Potentiometer(Pin pin, int min = -1, int max = -1);
    Potentiometer(Multiplexer & multiplexer, Pin pin, int min = -1, int max = -1);

    Event check();
    int read();

private:
    int _min;
    int _max;
    int _previous;
};

} // controlino
