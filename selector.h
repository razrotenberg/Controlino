#pragma once

namespace controlino
{

struct Selector
{
    Selector(char S0, char S1, char S2, char S3);
    
    void select(char pin);

private:
    char _S0; // lsb
    char _S1;
    char _S2;
    char _S3; // msb
};

} // controlino
