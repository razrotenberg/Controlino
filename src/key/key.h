#pragma once

#include "control/control.h"

namespace controlino
{

struct Key : Control
{
    enum class Event : char
    {
        None, // nothing has happened

        Down,
        Up,
        Hold,
    };

    Key(Pin pin);
    Key(Multiplexer & multiplexer, Pin pin);

    Event check();

private:
    bool _previous = false;
};

} // controlino
