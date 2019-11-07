#include "control.h"

#include <Arduino.h>

namespace controlino
{

Control::Control(char pin, Multiplexer * multiplexer) :
    _pin(pin),
    _multiplexer(multiplexer)
{
    if (_multiplexer == nullptr)
    {
        pinMode(_pin, INPUT_PULLUP);
    }
}

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

} // controlino
