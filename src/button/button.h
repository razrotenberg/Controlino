#pragma once

#include "../control/control.h"

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

    // 16 bits can hold 65,535 possible values, which is enough for storing information for ~65 seconds
    // Arduino's `millis()` returns an `unsigned long` which overflows back to (0) after approximately 50 days.
    // when we take the 16 lsbs (2 bytes) we receive a number that will overflow after every ~65 seconds.
    // therefore, in order to be able to correctly compare time differences, we have to calculate the time
    // difference only at one side of the furmula:
    //   good: `now - _when > 1000`
    //   bad:  `now > _whan + 1000`
    // this will cause the overflow to "correct itself" when it's in the same side of the formula
    //
    // example:
    //   unsigned short a = 1;
    //   unsigned short b = USHRT_MAX;
    //   unsigned short c = a - b;
    //   std::cout << c << std::endl; // will print 2
    //
    unsigned short _when;
};

} // controlino
