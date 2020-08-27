# Controlino

*Controlino* is a library that eases the use of physical input controls connected the Arduino directly or through a multiplexer.

Written in C++ and offering easy control of potentiometers and buttons, while supporting simple and complex gestures of buttons such as down/up/click/double-click/press/click-and-press.

---

## Overview

*Controlino* is written in a C++ manner.
It supports several input controls (all documented below). All input controls can be connected directly to the Arduino or through a multiplexer, and their usage is kept the same for the user.

Currently, there is support for 8-channel and 16-channel multiplexers, but additional support should be easy to add.

The user should periodically call the `check()` method of all controls. A good example is to do it in an interrupt handler every a few milliseconds, or from the global `loop()` method.
`Control` objects store their current state and update it on every call to `check()`.

The method `check()` returns an `Event` enum to indicate events that happen to the control (e.h. `Click`, `Down`, `Hold`).
The enum `Event` is a different one for every class, and has different options. All options are documented below, for every control.

## Controls

### Key

A simple button switch control.

A `Key` control should be connected to the builtin pullup resistors.
Therefore, in case of a physical button switch, on leg should be connected to GND, while the other one should be connected to the Arduino.

The following table lists the options of `Key::Event`:

| Event | Description | Details |
|-------|-------------|---------|
| `None` | The key is still not pressed | The key was previously not pressed and it is now not pressed |
| `Down` | The key was just pressed | The key was previously not pressed and it is now pressed |
| `Up` | The key was just released | The key was previously pressed and it is now not pressed |
| `Hold` | The key is still pressed | The key was previously pressed and it is now pressed |

> Take a look at the "key" [example](examples/Key/Key.ino) for a usage example.

### Button

A complex button switch control.

A `Button` control should be connected to the builtin pullup resistors.
Therefore, in case of a physical button switch, on leg should be connected to GND, while the other one should be connected to the Arduino.

The following table lists the options of `Button::Event`:

| Event | Description | Details |
|-------|-------------|---------|
| `None` | The button is still not pressed | The button was previously not pressed and it is now not pressed |
| `Down` | The button was just pressed | The button was previously not pressed and it is now pressed |
| `Up` | The button was just released | The button was previously pressed and it is now not pressed |
| `Click` | The button was clicked | The button was just released after being pressed once for a short duration |
| `Press` | The button was pressed | The button was pressed once and is still pressed for a long duration |
| `ClickClick` | The button was clicked twice | The button was just released after being pressed twice for a short duration |
| `ClickPress` | The button was clicked and pressed | The button was clicked for a short duration and then pressed and is still pressed for a long duration |

> Take a look at the "button" [example](examples/Button/Button.ino) for a usage example.

### Potentiometer

A potentiometer control.

A `Potentiometer` control should be either connected directly to an analog pin of the Arduino, or through a multiplexer which its communication pin is connected to an analog pin.

The following table lists the options of `Potentiometer::Event`:

| Event | Description | Details |
|-------|-------------|---------|
| `None` | The potentiometer was not moved | The current value of the potentiometer is equal to the previous one |
| `Changed` | The potentiometer was moved | The current value of the potentiometer is different than the previous one |

In addition, `Potentiometer` exposes the method `int read()` to read the current value of the control.

Upon creation, `Potentiometer` may receive minimum and maximum values, and the value returned from `read()` will be limited by them.

During development and because of the usage of a solderless breadboard, it's common for potentiometers to be unstable.
For this reason, `Potentiometer` receives parameters, encapsulated in `Potentiometer::Noise`, that could be configured according to the current setup, to improve the stability:
- `down` - a floating point multiplier for `min`
- `up` - a floating point multiplier for `max`
- `fluctuation` - the noise threshold

Both `down` and `up` are used for multiplying `min` and `max`, respectively.
They are used for decreasing and increasing `min` and `max` to improve the mapping of the raw values of the potentiometer from (0..1023) to (min..max)

> Take a look at the "potentiometer" [example](examples/Potentiometer/Potentiometer.ino) for a usage example.

## Classes

### Pin

A typedef of `char` to be used for pin numbers.

### Pinmode

A utility class to hold information of both a pin number and a pin behavior (mode).

`Pinmode` stores the information in a single byte (a `char`). It stores the pin mode in the 2 msbs, and the pin number in the 6 lsbs.
2 bits are enough for storing the 3 possible modes (`INPUT`, `OUTPUT`, `INPUT_PULLUP`), and 6 bits are enough for storing pin numbers up to 64.

### Selector

A utility class which is used by `Multiplexer` to easily control the select pins of a multiplexer. Currently supporting 8 channel (3 bit) and 16 channel (4 bit) multiplexers.

Upon creation, the select pin numbers should be passed to the object. Three pin numbers for a 8-channel (3-bit) selector, and four pin numbers for a 16-channel (4-bit) one.
The least-significant pin should be passed as the first argument, and the most-significant pin should be passed as the last argument.

`Selector` exposes the method `select(Pin pin)` to write values to the select pins in order for pin `pin` to be passed by the multiplexer.

### Multiplexer

A class to ease digital and analog reads of multiplexed pins.

Upon creation, a `Selector` object must be passed to `Multiplexer`, as well as the communication pin number.
The `Multiplexer` class holds a weak reference to a `Selector` object, to allow several `Multiplexer`s can share the same `Selector` object.

Currently, `Multiplexer` supports input communication only. Output communication sould be easy to add in the future as well.

`Multiplexer` supports passing both digital and analog communication, and exposes two methods with an API similar to the Arduino:
* `int digitalRead(Pin pin)`
* `int analogRead(Pin pin)`

Both methods receive an argument `pin` which is the pin number behind the multiplexer. This value will be selected using `Selector` before reading the value of the communication pin.

Pins behind the multiplexer can be of different input controls. There could be digital and analog pins being multiplexed at the same time, as well as pins that should be connected to the builtin pullup resistors.
Therefore, every time one wants to read the value that is passed by the multiplexer (using one ot the two methods above), he or she should configure the communication pin to the desired behavior.
This could be done by using the method `piMode(Mode mode)` of `Multiplexer` that configures the behavior of the communication pin to the specified mode.
To avoid reconfiguring the communication pin if it is already configured as desired, `pinMode()` will configure its behavior only if the pin is currently configured to a different behavior, or if it was never configured.

### Control

The base class from which all controls inherit.

Every `Control` object represent a physical control on the board, connected to the Arduino, and should be of a specific pin behavior. Pin behaviors cannot be changed during runtime.

Every physical control could be behind a multiplexer or not. Upon creation, a pin number and a pin mode (behavior) are passed to `Control`.
In case the control is connected through a multiplexer, the respective `Multiplexer` object is to be passed upon creation, and a weak reference to it is stored in the object.

If the control is connected through a multiplexer, the pin number represents the channel number of the multiplexer, and not the multiplexer's communication pin number.
Otherwise, if the control is connected directly, the pin number represents the actual pin number to which the control is connected.

If the control is connected through a multiplexer, the multiplexer's communication pin is configured - using `Multiplexer::pinMode()` - before every read of its value.
Otherwise, if the control is connected directly, the pin is configured exactly once, upon creation.
