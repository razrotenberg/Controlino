#include "selector.h"

#include <Arduino.h>

namespace controlino
{

Selector::Selector(char S0, char S1, char S2, char S3) :
    _S0(S0),
    _S1(S1),
    _S2(S2),
    _S3(S3)
{
    pinMode(_S0, OUTPUT);
    pinMode(_S1, OUTPUT);
    pinMode(_S2, OUTPUT);
    pinMode(_S3, OUTPUT);
}

void Selector::select(char pin)
{
    digitalWrite(_S0, (pin & 0b0001) ? HIGH : LOW);
    digitalWrite(_S1, (pin & 0b0010) ? HIGH : LOW);
    digitalWrite(_S2, (pin & 0b0100) ? HIGH : LOW);
    digitalWrite(_S3, (pin & 0b1000) ? HIGH : LOW);
}
    
} // controlino
