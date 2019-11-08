#include "multiplexer.h"

#define PIN (_comm & 0b00111111)

namespace controlino
{

Multiplexer::Multiplexer(char comm, Selector & selector) :
    _comm(comm | 0b11000000), // 0b11 (3) is not a valid mode and will cause the mode to be set at the first usage
    _selector(selector)
{}

int Multiplexer::digitalRead(char pin)
{
    set(Mode::Pullup);
    _selector.select(pin);
    return ::digitalRead(PIN);
}

int Multiplexer::analogRead(char pin)
{
    set(Mode::Input);
    _selector.select(pin);
    return ::analogRead(PIN);
}

void Multiplexer::set(Mode mode)
{
    // 2 bits are enough for representing the possible 3 modes

    const auto desired = static_cast<char>(mode) << 6;
    const auto current = _comm & 0b11000000;

    if (desired != current)
    {
        pinMode(PIN, static_cast<char>(mode));
        _comm &= 0b00111111;
        _comm |= desired;
    }
}

} // controlino
