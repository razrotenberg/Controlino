#include "potentiometer.h"

namespace controlino
{

Potentiometer::Potentiometer(Pin pin) : Control(pin, Mode::Input),
    _previous(analogRead())
{}

Potentiometer::Potentiometer(Multiplexer & multiplexer, Pin pin) : Control(multiplexer, pin, Mode::Input),
    _previous(analogRead())
{}

int Potentiometer::check()
{
    int value = -1;
    (void)check(/* out */ value);
    return value;
}

bool Potentiometer::check(/* out */ int & value)
{
    const auto current = analogRead();

    if (abs(current - _previous) <= 2) // ignore noise
    {
        return false;
    }

    /* out */ value = _previous = current;
    return true;
}

} // controlino
