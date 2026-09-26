# Arduino Robot Tank

Firmware for a Keyestudio tracked robot on an Arduino Uno. The robot has four modes that are
switched from the IR remote, and shows the current one on its LED matrix.

## Remote

| Key | Action |
| --- | --- |
| `1` | Manual: arrows drive, the robot keeps moving until another key |
| `2` | Light follow: drives toward a flashlight |
| `3` | Obstacle avoid: drives on its own and looks around with the sonar when blocked |
| `4` | Serial: `U` `D` `L` `R` `S` commands at 9600 baud (Bluetooth module or USB) |
| `OK` | Stop and go back to manual, from any mode |
| `*` | Toggle the front LED |
| `#` | "MA MA hi" greeting on the LED matrix |

## Wiring

| Part | Pins |
| --- | --- |
| Left motor | direction `D13`, PWM `D11` |
| Right motor | direction `D12`, PWM `D3` |
| IR receiver | `A0` |
| Photoresistors | left `A1`, right `A2` |
| LED matrix | SDA `A4`, SCL `A5` |
| Ultrasonic sensor | trig `D5`, echo `D4` |
| Servo | `D9` |
| Front LED | `D10` |

## Project layout

```
include/          board.h (pins), config.h (speeds, thresholds), remote_keys.h
lib/drivers/      motors, sonar, LED matrix, IR remote, LED - the only code that touches hardware pins
lib/navigation/   decisions as plain functions, no Arduino dependency
src/main.cpp      creates the objects, reads the remote, runs the active mode
src/modes/        one class per mode behind the Mode interface
test/             unit tests for lib/navigation, run on the host
```

A few things worth knowing before changing the code:

- Nothing in the main loop blocks. Obstacle avoidance and the greeting are state machines on
  `millis()`, so the remote always responds. The one exception is the sonar reading, which
  waits for the echo for up to 25 ms.
- Drivers get their pins through the constructor. The IR receiver is the exception:
  TinyIRReceiver picks the pin with the preprocessor, so it is set in `ir_remote.cpp`.
- No dynamic memory. All objects are static and the matrix images live in flash.

### Timers

The Uno has three timers and all of them are taken:

- Timer0: `millis()`.
- Timer1: the Servo library. This is why the front LED on `D10` is on/off only.
- Timer2: PWM for the motors on `D3` and `D11`. The regular IRremote receiver also wants
  Timer2, so the remote is read with TinyIRReceiver, which uses a pin change interrupt.

## Build

The project uses [PlatformIO](https://platformio.org/). Libraries are downloaded on the first build.

```sh
pio run                 # build
pio run -t upload       # flash
pio device monitor      # serial log at 9600 baud
pio test -e native      # unit tests on the host
```

Unplug the Bluetooth module while flashing over USB: it sits on the same `D0`/`D1` pins.
