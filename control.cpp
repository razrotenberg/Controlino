#include "control.h"

#include <Arduino.h>

namespace controlino
{

Control::Control(Pin pin, Mode mode) :
    _pinmode(pin, mode),
    _multiplexer(nullptr)
{
    pinMode(pin, (char)mode);
}

Control::Control(Multiplexer & multiplexer, Pin pin, Mode mode) :
    _pinmode(pin, mode),
    _multiplexer(&multiplexer)
{}

int Control::digitalRead()
{
    if (_multiplexer != nullptr)
    {
        _multiplexer->pinMode(_pinmode.mode());
        return _multiplexer->digitalRead(_pinmode.pin());
    }
    else
    {
        return ::digitalRead(_pinmode.pin());
    }
}

int Control::analogRead()
{
    if (_multiplexer != nullptr)
    {
        _multiplexer->pinMode(_pinmode.mode());
        return _multiplexer->analogRead(_pinmode.pin());
    }
    else
    {
        return ::analogRead(_pinmode.pin());
    }
}

} // controlino
