#include "control.h"

#include <Arduino.h>

namespace controlino
{

Control::Control(char pin, Mode mode) :
    _pin(pin),
    _multiplexer(nullptr)
{
    pinMode(_pin, static_cast<char>(mode));
}

Control::Control(Multiplexer & multiplexer, char pin) :
    _pin(pin),
    _multiplexer(&multiplexer)
{}

bool Control::digitalRead()
{
    if (_multiplexer != nullptr)
    {
        return _multiplexer->digitalRead(_pin) == LOW;
    }
    else
    {
        return ::digitalRead(_pin) == LOW;
    }
}

int Control::analogRead()
{
    if (_multiplexer != nullptr)
    {
        return _multiplexer->analogRead(_pin);
    }
    else
    {
        return ::analogRead(_pin);
    }
}

} // controlino
