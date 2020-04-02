#include "key.h"

namespace controlino
{

Key::Key(char pin) : Control(pin, Mode::Pullup)
{}

Key::Key(Multiplexer & multiplexer, char pin) : Control(multiplexer, pin)
{}

Key::Event Key::check()
{
    auto event = Event::None;

    const auto pressed = digitalRead();

    if (pressed == true && _previous == false)
    {
        event = Event::Down;
    }
    else if (pressed == false && _previous == true)
    {
        event = Event::Up;
    }
    else if (pressed == true && _previous == true)
    {
        event = Event::Hold;
    }

    _previous = pressed;
    return event;
}

} // controlino
