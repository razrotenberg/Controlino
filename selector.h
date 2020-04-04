#pragma once

#include "pin.h"

namespace controlino
{

struct Selector
{
    Selector(Pin S0, Pin S1, Pin S2); // 8 channels (3 bits)
    Selector(Pin S0, Pin S1, Pin S2, Pin S3); // 16 channels (4 bits)

    void select(Pin pin);

private:
    Pin _pins[4]; // [lsb...msb]
};

} // controlino
