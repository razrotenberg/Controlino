#pragma once

#include "multiplexer.h"
#include "pinmode.h"

namespace controlino
{

struct Control
{
protected:
    Control(Pin pin, Mode mode);
    Control(Multiplexer & multiplexer, Pin pin, Mode mode);

    int digitalRead();
    int analogRead();

private:
    Pinmode _pinmode;
    Multiplexer * _multiplexer;
};

} // controlino
