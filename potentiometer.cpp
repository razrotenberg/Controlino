#include "potentiometer.h"

namespace controlino
{

Potentiometer::Potentiometer(char pin) : _pin(pin)
{
    pinMode(pin, INPUT);
    _previous = analogRead(pin);
}

int Potentiometer::check()
{
    int value = -1;
    (void)check(/* out */ value);
    return value;
}

bool Potentiometer::check(/* out */ int & value)
{
    const auto current = analogRead(_pin);

    if (abs(current - _previous) <= 2) // ignore noise
    {
        return false;
    }

    /* out */ value = _previous = current;
    return true;
}

} // controlino
