#include "key.h"

using namespace controlino;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    static Key __key(2);

    const auto event = __key.check();

    if (event == Key::Event::Down)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Down");
    }
    else if (event == Key::Event::Up)
    {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Up");
    }
}
