#include "selector.h"

#include <Arduino.h>

namespace controlino
{

Selector::Selector(char S0, char S1, char S2) :
    _S0(S0),
    _S1(S1),
    _S2(S2)
{
    pinMode(_S0, OUTPUT);
    pinMode(_S1, OUTPUT);
    pinMode(_S2, OUTPUT);
}

void Selector::select(char pin)
{
    digitalWrite(_S0, (pin & 0b001) ? HIGH : LOW);
    digitalWrite(_S1, (pin & 0b010) ? HIGH : LOW);
    digitalWrite(_S2, (pin & 0b100) ? HIGH : LOW);
}
    
} // controlino
