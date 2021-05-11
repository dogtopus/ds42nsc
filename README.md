# Hacky DS4 to Switch (Pokken) Controller Converter

This is an one-hour side project after I saw this [PR by earboxer][pr]. It plays BoTW just fine.

## Hardware

- Teensy 3.x/LC (mostly tested on LC)
- USB Host Shield (mini is preferred)
  - Refer to the [UHS library GitHub][uhs] for wiring.

## Building

### PlatformIO

0. Go to the release section and download the 2 zip files (contains the prepatched teensyduino library)
1. Unzip `framework-arduinoteensy-ns_1.145.0.zip` and put contents under `~/.platformio/packages`.
2. Unzip `teensy-ns_4.3.0.zip` and put contents under `~/.platformio/platforms`.
3. Run `platformio run` (or `platformio run -e teensylc-mega69`) and hopefully nothing will break.

(For Teensy 3.x, use `-e teensy{31,35,36}[-mega69]` instead)

### Teensyduino (not tested)

0. Follow the instruction in the [original PR][pr]
1. Download and install USB Host Shield Library (and SPI4Teensy3 if you are building for 3.x).
2. Make a directory called `ds42nsc` somewhere.
3. Copy `src/main.cpp` to `ds42nsc` and rename it `ds42nsc.ino`.
4. Add `#define MEGA69` at the beginning of `ds42nsc.ino` to enable MEGA69 mode.
5. Open it with Arduino IDE and hit upload (and hopefully nothing will break as well).

## Usage

1. Plug the DS4 into the USB Host Shield
2. Plug the Teensy into Switch
3. Plug in external VBUS power supply for USB Host Shield (if you have one. For LC this is pretty much mandatory due to small VBUS fuse.)
4. ???
5. PROFIT!

## Note

The Minus key (-) on the switch controller is mapped to the touchpad click on DS4 and the Capture key is mapped to the Share key. This is to preserve the meaning of the Share key. Besides that, Minus as touchpad click also feels native in BoTW since a lot of PS4 games of similar genre use the touchpad click for opening map as well.

[pr]: https://github.com/PaulStoffregen/cores/pull/386
[uhs]: https://github.com/felis/USB_Host_Shield_2.0
