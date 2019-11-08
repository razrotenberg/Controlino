#pragma once

#include "control.h"

namespace controlino
{

struct Key : Control
{
    enum class Event : char
    {
        None, // nothing has happened
        
        Down,
        Up,
    };

    Key(char pin);
    Key(Multiplexer & multiplexer, char pin);

    Event check();

private:
    bool _previous = false;
};

} // controlino
