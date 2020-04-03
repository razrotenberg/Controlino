#pragma once

#include "mode.h"
#include "pin.h"

namespace controlino
{

struct Pinmode
{
    Pinmode(Pin pin, Mode mode);

    // setters
    void pin(Pin value);
    void mode(Mode value);

    // getters
    Pin pin() const;
    Mode mode() const;

private:
    // 2 msbs are the mode and are enough to represent the possible 3 modes
    // 6 lsbs are the pin and are enough to represent numbers up to 64
    char _data;
};

} // controlino
