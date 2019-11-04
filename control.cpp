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
        pinMode(_pin, INPUT);
    }
}

bool Control::digitalRead()
{
    if (_multiplexer != nullptr)
    {
        return _multiplexer->digitalRead(_pin) == HIGH;
    }
    else
    {
        return ::digitalRead(_pin) == HIGH;
    }
}

} // controlino
