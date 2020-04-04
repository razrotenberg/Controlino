#include <Controlino.h>

// `MUXED` should be defined if the button is connected through a multiplexer
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

constexpr Pin SIG = 6;

constexpr Pin Button = 0;

#else

constexpr Pin Button = 7;

#endif

}; // pin
}; //

extern "C" void setup()
{
    Serial.begin(9600);
}

extern "C" void loop()
{
#ifdef MUXED
    static auto __selector      = Selector(pin::S0, pin::S1, pin::S2, pin::S3);
    static auto __multiplexer   = Multiplexer(pin::SIG, __selector);
    static auto __button        = Button(__multiplexer, pin::Button);
#else
    static auto __button        = Button(pin::Button);
#endif

    const auto event = __button.check();

    if      (event == Button::Event::Down)       { Serial.println("Down");       }
    else if (event == Button::Event::Up)         { Serial.println("Up");         }
    else if (event == Button::Event::Click)      { Serial.println("Click");      }
    else if (event == Button::Event::Press)      { Serial.println("Press");      }
    else if (event == Button::Event::ClickClick) { Serial.println("ClickClick"); }
    else if (event == Button::Event::ClickPress) { Serial.println("ClickPress"); }
}

} // controlino
