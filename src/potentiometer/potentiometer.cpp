#include "potentiometer.h"

namespace controlino
{

Potentiometer::Potentiometer(Pin pin, const Noise & noise) : Potentiometer(pin, -1, -1, noise)
{}

Potentiometer::Potentiometer(Pin pin, int min, int max, const Noise & noise) : Control(pin, Mode::Input),
    _min(min),
    _max(max),
    _noise(noise),
    _previous(analogRead())
{}

Potentiometer::Potentiometer(Multiplexer & multiplexer, Pin pin, const Noise & noise) : Potentiometer(multiplexer, pin, -1, -1, noise)
{}

Potentiometer::Potentiometer(Multiplexer & multiplexer, Pin pin, int min, int max, const Noise & noise) : Control(multiplexer, pin, Mode::Input),
    _min(min),
    _max(max),
    _noise(noise),
    _previous(analogRead())
{}

Potentiometer::Event Potentiometer::check()
{
    auto event = Event::None;

    const int now = analogRead();

    if (abs(now - _previous) > _noise.fluctuation)
    {
        _previous = now;
        event = Event::Changed;
    }

    return event;
}

int Potentiometer::read()
{
    int value = _previous;

    if (_min != -1 && _max != -1)
    {
        value = constrain(
            map(value, 0, 1023, (int)((float)_min * _noise.down), (int)((float)_max * _noise.up)),
            _min, _max);
    }

    return value;
}

} // controlino
