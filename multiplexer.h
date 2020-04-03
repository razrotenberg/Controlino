#pragma once

#include "pinmode.h"
#include "selector.h"

namespace controlino
{

struct Multiplexer
{
    Multiplexer(Pin comm, Selector & selector);

    int digitalRead(Pin pin);
    int analogRead(Pin pin);

    void pinMode(Mode mode);

private:
    Pinmode _comm;
    Selector & _selector;
};

} // controlino
