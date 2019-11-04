#pragma once

namespace controlino
{

struct Selector
{
    Selector(char S0, char S1, char S2);
    
    void select(char pin);

private:
    char _S0; // lsb
    char _S1;
    char _S2; // msb
};

} // controlino
