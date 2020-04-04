#include "key.h"

namespace controlino
{

Key::Key(Pin pin) : Control(pin, Mode::Pullup)
{}

Key::Key(Multiplexer & multiplexer, Pin pin) : Control(multiplexer, pin, Mode::Pullup)
{}

Key::Event Key::check()
{
    auto event = Event::None;

    const auto pressed = digitalRead() == LOW;

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
