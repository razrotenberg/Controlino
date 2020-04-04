#include "pinmode.h"

namespace controlino
{

Pinmode::Pinmode(Pin pin, Mode mode)
{
    this->pin(pin);
    this->mode(mode);
}

void Pinmode::pin(Pin value)
{
    _data &= 0b11000000;
    _data |= (value & 0b00111111);
}

void Pinmode::mode(Mode value)
{
    _data &= 0b00111111;
    _data |= (((char)value << 6) & 0b11000000);
}

Pin Pinmode::pin() const
{
    return (Pin)(_data & 0b00111111);
}

Mode Pinmode::mode() const
{
    return (Mode)((_data >> 6) & 0b00000011);
}

} // controlino
