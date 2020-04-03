#pragma once

#include "control.h"

#include <Arduino.h>

namespace controlino
{

struct Potentiometer : Control
{
    Potentiometer(Pin pin);
    Potentiometer(Multiplexer & multiplexer, Pin pin);

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

        /* out */ value = constrain(
            map(value, 0, 1023, (int)((float)Min * 0.85), (int)((float)Max * 1.15)),
            Min, Max);

        return true;
    }

    template <int Min, int Max>
    int read()
    {
        const auto value = analogRead();

        return constrain(
            map(value, 0, 1023, (int)((float)Min * 0.85), (int)((float)Max * 1.15)),
            Min, Max);
    }

private:
    int _previous;
};

} // controlino
