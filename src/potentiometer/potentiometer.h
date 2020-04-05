#pragma once

#include "../control/control.h"

#include <Arduino.h>

namespace controlino
{

template <int Min, int Max>
struct Potentiometer : Control
{
    enum class Event : char
    {
        None, // nothing has happened

        Changed,
    };

    Potentiometer(Pin pin) : Control(pin, Mode::Input),
        _previous(read())
    {}

    Potentiometer(Multiplexer & multiplexer, Pin pin) : Control(multiplexer, pin, Mode::Input),
        _previous(read())
    {}

    Event check()
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
