#include <Controlino.h>

// `MUXED` should be defined if the key is connected through a multiplexer
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

constexpr Pin Key = 0;

#else

constexpr Pin Key = 7;

#endif

}; // pin
}; //

extern "C" void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

extern "C" void loop()
{
#ifdef MUXED
    static auto __selector      = Selector(pin::S0, pin::S1, pin::S2, pin::S3);
    static auto __multiplexer   = Multiplexer(pin::SIG, __selector);
    static auto __key           = Key(__multiplexer, pin::Key);
#else
    static auto __key           = Key(pin::Key);
#endif

    const auto event = __key.check();

    if (event == Key::Event::Down)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Down");
    }
    else if (event == Key::Event::Hold)
    {
        static unsigned long __millis = -1;

        if (__millis == -1 || millis() - __millis > 200)
        {
            Serial.println("Hold");
            __millis = millis();
        }
    }
    else if (event == Key::Event::Up)
    {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Up");
    }
}

} // controlino
