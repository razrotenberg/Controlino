#pragma once

#include "mode.h"
#include "multiplexer.h"

namespace controlino
{

struct Control
{
protected:
    Control(char pin, Mode mode);
    Control(Multiplexer & multiplexer, char pin);

    bool digitalRead();

private:
    char _pin;
    Multiplexer * _multiplexer;
};

} // controlino
