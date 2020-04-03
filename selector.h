#pragma once

#include "pin.h"

namespace controlino
{

struct Selector
{
    Selector(Pin S0, Pin S1, Pin S2, Pin S3);

    void select(Pin pin);

private:
    Pin _S0; // lsb
    Pin _S1;
    Pin _S2;
    Pin _S3; // msb
};

} // controlino
