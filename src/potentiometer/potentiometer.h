#pragma once

#include "../control/control.h"

#include <Arduino.h>

namespace controlino
{

template <int Min, int Max>
struct Potentiometer : Control
{
    enum class Event : char
    {
        None, // nothing has happened

        Changed,
    };

    Potentiometer(Pin pin) : Control(pin, Mode::Input),
        _value(read())
    {}

    Potentiometer(Multiplexer & multiplexer, Pin pin) : Control(multiplexer, pin, Mode::Input),
        _value(read())
    {}

    Event check()
    {
        auto event = Event::None;

        const auto now = millis();
        const auto value = read();

        if (_millis == -1 && _value != value)
        {
            _millis = now;
            _prospect = value; // `value` is now a prospect

            // Serial.print("[A] now: ");
            // Serial.print(now);
            // Serial.print("; _value: ");
            // Serial.print(_value);
            // Serial.print("; _prospect: ");
            // Serial.print(_prospect);
            // Serial.println(' ');
        }
        else if (_millis != -1 && _prospect == value && now - _millis > 100)
        {
            // Serial.print("[B] now: ");
            // Serial.print(now);
            // Serial.print("; _millis: ");
            // Serial.print(_millis);
            // Serial.print("; diff: ");
            // Serial.print(now - _millis);
            // Serial.print("; _value: ");
            // Serial.print(_value);
            // Serial.print("; _prospect: ");
            // Serial.print(_prospect);
            // Serial.println(' ');

            // enough time has passed since we started to examine 'value'
            _millis = -1;
            _value = value;
            event = Event::Changed;
        }
        else if (_millis != -1 && _value == value)
        {
            // Serial.print("[C] now: ");
            // Serial.print(now);
            // Serial.print("; _millis: ");
            // Serial.print(_millis);
            // Serial.print("; diff: ");
            // Serial.print(now - _millis);
            // Serial.print("; _value: ");
            // Serial.print(_value);
            // Serial.print("; _prospect: ");
            // Serial.print(_prospect);
            // Serial.println(' ');

            // we have been examining something in vain
            _millis = -1;
        }
        else if (_millis != -1 && _prospect != value /* && _value != value */)
        {
            // Serial.print("[D] now: ");
            // Serial.print(now);
            // Serial.print("; _millis: ");
            // Serial.print(_millis);
            // Serial.print("; diff: ");
            // Serial.print(now - _millis);
            // Serial.print("; _value: ");
            // Serial.print(_value);
            // Serial.print("; _prospect: ");
            // Serial.print(_prospect);
            // Serial.print("; value: ");
            // Serial.print(value);
            // Serial.println(' ');

            _millis = now;
            _value = _prospect;
            _prospect = value;
            event = Event::Changed;
        }

        // if (_value != value)
        // {
        //     event = Event::Changed;
        // }

        // _value = value;
        return event;
    }

    int value() const
    {
        return _value;
    }

private:
    int read()
    {
        const auto value = analogRead();

        return constrain(
            map(value, 0, 1023, (int)((float)Min * 0.85), (int)((float)Max * 1.15)),
            Min, Max);
    }

    int _value;
    int _prospect;
    unsigned long _millis = -1;
};

} // controlino
