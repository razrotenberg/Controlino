#pragma once

#include "multiplexer.h"

namespace controlino
{

struct Control
{
protected:
    Control(char pin, Multiplexer * multiplexer = nullptr);

    bool digitalRead();

private:
    char _pin;
    Multiplexer * _multiplexer;
};

} // controlino
