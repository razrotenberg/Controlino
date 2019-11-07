#include "button.h"

using namespace controlino;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    static Button __button(2);

    const auto event = __button.check();

    if      (event == Button::Event::Down)       { Serial.println("Down");       }
    else if (event == Button::Event::Up)         { Serial.println("Up");         }
    else if (event == Button::Event::Click)      { Serial.println("Click");      }
    else if (event == Button::Event::Press)      { Serial.println("Press");      }
    else if (event == Button::Event::ClickClick) { Serial.println("ClickClick"); }
    else if (event == Button::Event::ClickPress) { Serial.println("ClickPress"); }
}
