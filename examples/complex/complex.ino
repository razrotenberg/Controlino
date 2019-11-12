#include <Controlino.h>

using namespace controlino;

namespace pin
{
    constexpr auto S0 = 2;
    constexpr auto S1 = 3;
    constexpr auto S2 = 4;
    constexpr auto S3 = 5;
    
    constexpr auto SIG = A5;
}; // pin

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    static Selector __selector(pin::S0, pin::S1, pin::S2, pin::S3);
    static Multiplexer __multiplexer(pin::SIG, __selector);
        
    static Button __buttons[] = {
        { __multiplexer, 0 },
        { 10 },
    };

    for (auto & button : __buttons)
    {
        const auto event = button.check();

        if      (event == Button::Event::Down)       { Serial.println("Down");       }
        else if (event == Button::Event::Up)         { Serial.println("Up");         }
        else if (event == Button::Event::Click)      { Serial.println("Click");      }
        else if (event == Button::Event::Press)      { Serial.println("Press");      }
        else if (event == Button::Event::ClickClick) { Serial.println("ClickClick"); }
        else if (event == Button::Event::ClickPress) { Serial.println("ClickPress"); }
    }

    static Key __keys[] = {
        { __multiplexer, 5 },
        { 9 },
    };

    for (auto & key : __keys)
    {
        const auto event = key.check();

        if      (event == Key::Event::Down) { Serial.println("Down"); }
        else if (event == Key::Event::Up)   { Serial.println("Up");   }
    }

    static Potentiometer __potentiometers[] = {
        { __multiplexer, 10 },
        { A0 },
    };

    for (auto & potentiometer : __potentiometers)
    {
        const auto value = potentiometer.check<40, 230>();

        if (value != -1)
        {
            Serial.println(value);
        }
    }
}
