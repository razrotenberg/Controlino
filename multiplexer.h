#pragma once

#include "mode.h"
#include "selector.h"

namespace controlino
{

struct Multiplexer
{
    Multiplexer(char comm, Selector & selector);

    int digitalRead(char pin); // reading as input pullup
    int analogRead(char pin);

private:
    void set(Mode mode);

    char _comm; // 2 msbs are the current pin mode
    Selector & _selector;
};

} // controlino
