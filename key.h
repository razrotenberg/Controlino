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

    Key(char pin, Multiplexer * multiplexer = nullptr);

    Event check();

private:
    bool _previous;
};

} // controlino
