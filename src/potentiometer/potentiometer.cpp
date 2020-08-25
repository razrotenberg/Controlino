#include "potentiometer.h"

namespace controlino
{

Potentiometer::Potentiometer(Pin pin, int min, int max) : Control(pin, Mode::Input),
    _min(min),
    _max(max),
    _previous(read())
{}

Potentiometer::Potentiometer(Multiplexer & multiplexer, Pin pin, int min, int max) : Control(multiplexer, pin, Mode::Input),
    _min(min),
    _max(max),
    _previous(read())
{}

Potentiometer::Event Potentiometer::check()
{
    auto event = Event::None;

    const auto value = read();

    if (_previous != value)
    {
        event = Event::Changed;
    }

    _previous = value;
    return event;
}

int Potentiometer::read()
{
    int value = analogRead();

    if (_min != -1 && _max != -1)
    {
        value = constrain(
            map(value, 0, 1023, (int)((float)_min * 0.85), (int)((float)_max * 1.15)),
            _min, _max);
    }

    return value;
}

} // controlino
