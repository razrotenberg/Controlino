#pragma once

#include "selector.h"

namespace controlino
{

struct Multiplexer
{
    Multiplexer(char comm, Selector & selector);

    int digitalRead(char pin);

private:
    char _comm;
    Selector & _selector;
};

} // controlino
