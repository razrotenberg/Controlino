#pragma once

#include "control.h"

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

    Button(char pin, Multiplexer * multiplexer = nullptr);
    
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
    
    What _what;
    unsigned short _when; // 16 bits can hold 65,535 possible values, which is enough for storing information for ~65 seconds
};

} // controlino
