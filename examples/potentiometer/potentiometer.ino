#include "potentiometer.h"

using namespace controlino;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    static Potentiometer __potentiometer(A0);
    
    constexpr auto Min = 40;
    constexpr auto Max = 230;

    if (random(2) == 0) // first API
    {
        const auto value = __potentiometer.check<Min, Max>();
        if (value != -1)
        {
            Serial.println(value);
        }
    }
    else // second API
    {
        int value;
        if (__potentiometer.check<Min, Max>(/* out */ value))
        {
            Serial.println(value);
        }
    }
}
