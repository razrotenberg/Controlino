#include "multiplexer.h"

#include <Arduino.h>

namespace controlino
{

Multiplexer::Multiplexer(char comm, Selector & selector) :
    _comm(comm),
    _selector(selector)
{
    pinMode(_comm, INPUT_PULLUP);
}

int Multiplexer::digitalRead(char pin)
{
    _selector.select(pin);
    return ::digitalRead(_comm);
}

} // controlino
