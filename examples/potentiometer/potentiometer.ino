#include "potentiometer.h"

// `MUXED` should be defined if the potentiometer is connected through a multiplexer
// #define MUXED

namespace controlino
{

namespace
{
namespace pin
{

#ifdef MUXED

constexpr Pin S0 = 2;
constexpr Pin S1 = 3;
constexpr Pin S2 = 4;
constexpr Pin S3 = 5;

constexpr Pin SIG = A0;

constexpr Pin Potentiometer = 0;

#else

constexpr Pin Potentiometer = A0;

#endif

}; // pin
}; //

extern "C" void setup()
{
    Serial.begin(9600);
}

extern "C" void loop()
{
    using Potentiometer = Potentiometer<20, 230>;

#ifdef MUXED
    static auto __selector      = Selector(pin::S0, pin::S1, pin::S2, pin::S3);
    static auto __multiplexer   = Multiplexer(pin::SIG, __selector);
    static auto __potentiometer = Potentiometer(__multiplexer, pin::Potentiometer);
#else
    static auto __potentiometer = Potentiometer(pin::Potentiometer);
#endif

    if (__potentiometer.check() == Potentiometer::Event::Changed)
    {
        Serial.println(__potentiometer.read());
    }
}

} // controlino
