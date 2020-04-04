#include "multiplexer.h"

namespace controlino
{

Multiplexer::Multiplexer(Pin comm, Selector & selector) :
    _comm(comm, (Mode)0b11), // 0b11 (3) is not a valid mode and will cause the pin to be configured at the first usage
    _selector(selector)
{}

int Multiplexer::digitalRead(Pin pin)
{
    _selector.select(pin);
    return ::digitalRead(_comm.pin());
}

int Multiplexer::analogRead(Pin pin)
{
    _selector.select(pin);
    return ::analogRead(_comm.pin());
}

void Multiplexer::pinMode(Mode mode)
{
    if (mode != _comm.mode())
    {
        ::pinMode(_comm.pin(), (char)mode);
        _comm.mode(mode);
    }
}

} // controlino
