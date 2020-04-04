#include "selector.h"

#include <Arduino.h>

namespace controlino
{

Selector::Selector(Pin S0, Pin S1, Pin S2) : Selector(S0, S1, S2, -1)
{}

Selector::Selector(Pin S0, Pin S1, Pin S2, Pin S3)
{
    _pins[0] = S0;
    _pins[1] = S1;
    _pins[2] = S2;
    _pins[3] = S3;

    for (unsigned i = 0; i < sizeof(_pins) / sizeof(_pins[0]); ++i)
    {
        if (_pins[i] != -1)
        {
            pinMode(_pins[i], OUTPUT);
        }
    }
}

void Selector::select(Pin pin)
{
    for (unsigned i = 0; i < sizeof(_pins) / sizeof(_pins[0]); ++i)
    {
        if (_pins[i] != -1)
        {
            digitalWrite(_pins[i], (pin & (1 << i)) ? HIGH : LOW);
        }
    }
}

} // controlino
