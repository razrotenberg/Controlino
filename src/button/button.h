#pragma once

#include "control/control.h"

namespace controlino
{

struct Button : Control
{
    enum class Event : char
    {
        None, // nothing has happened

        Down,
        Up,
        Click,
        Press,
        ClickClick,
        ClickPress,
    };

    Button(Pin pin);
    Button(Multiplexer & multiplexer, Pin pin);

    Event check();

private:
    enum class What : char
    {
        Idle,
        Touch,
        Press,
        Slip,
        Release,
        SecondPress,
        SecondRelease,
        Drain,
    };

    What _what = What::Idle;
    unsigned short _when; // 16 bits can hold 65,535 possible values, which is enough for storing information for ~65 seconds
};

} // controlino
