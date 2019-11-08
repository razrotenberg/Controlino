#pragma once

#include "control.h"

#include <Arduino.h>

namespace controlino
{

struct Potentiometer : Control
{
    Potentiometer(char pin);
    Potentiometer(Multiplexer & multiplexer, char pin);

    int check();

    template <int Min, int Max>
    int check()
    {
        int value = -1;
        (void)check<Min, Max>(/* out */ value);
        return value;
    }

    bool check(/* out */ int & value);

    template <int Min, int Max>
    bool check(/* out */ int & value)
    {
        if (!check(/* out */ value)) { return false; }
        /* out */ value = constrain(map(value, 0, 1023, Min, Max + 1), Min, Max);
        return true;
    }

private:
    int _previous;
};

} // controlino
