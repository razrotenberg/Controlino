#pragma once

#include <Arduino.h>

namespace controlino
{

enum class Mode : char
{
    Input  = INPUT, // pull down
    Output = OUTPUT,
    Pullup = INPUT_PULLUP,
};

} // controlino
