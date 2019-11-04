#include "key.h"

namespace controlino
{

Key::Key(char pin, Multiplexer * multiplexer) : Control(pin, multiplexer),
    _previous(false)
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

    _previous = pressed;
    return event;
}

} // controlino
