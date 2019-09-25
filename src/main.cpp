// SPDX-License-Identifier: Unlicense
/* ========================================
 *
 * "Copyright" dogtopus, 2019
 * Released to public domain
 *
 * ========================================
*/

#include <Arduino.h>
#include <EventResponder.h>

#include <usbhub.h>
#include <PS4USB.h>

USB USBH;
USBHub Hub1(&USBH);
PS4USB DS4(&USBH);

EventResponder USBHTaskEvent;
MillisTimer USBHTaskTimer;

// Switch assumes the controller would do calibration, so we'll "do it"
const uint8_t stick_centroid = 128;
const uint8_t stick_deadzone_radius = 10;

void setup() {
    Joystick.begin();
    Joystick.useManualSend(true);
    if (USBH.Init() == -1) {
        while (1);
    }
    // Enable power
    USBH.gpioWr(0x01);
    // Background task for USB host library
    USBHTaskEvent.attach([](EventResponderRef event) {
        USBH.Task();
    });
    // USBH is polled every 1ms
    USBHTaskTimer.beginRepeating(1, USBHTaskEvent);
}

uint8_t apply_dead_zone(uint8_t orig) {
    if (orig < stick_centroid - stick_deadzone_radius or orig > stick_centroid + stick_deadzone_radius) {
        return orig;
    } else {
        return stick_centroid;
    }
}

void loop() {
    if (DS4.connected()) {
        Joystick.DPad(DS4.getButtonPress(UP), DS4.getButtonPress(RIGHT), DS4.getButtonPress(DOWN), DS4.getButtonPress(LEFT));
        Joystick.X(apply_dead_zone(DS4.getAnalogHat(LeftHatX)));
        Joystick.Y(apply_dead_zone(DS4.getAnalogHat(LeftHatY)));
        Joystick.RX(apply_dead_zone(DS4.getAnalogHat(RightHatX)));
        Joystick.RY(apply_dead_zone(DS4.getAnalogHat(RightHatY)));
        Joystick.button(1, DS4.getButtonPress(SQUARE)); // Y
        Joystick.button(2, DS4.getButtonPress(CROSS)); // B
        Joystick.button(3, DS4.getButtonPress(CIRCLE)); // A
        Joystick.button(4, DS4.getButtonPress(TRIANGLE)); // X
        Joystick.button(5, DS4.getButtonPress(L1)); // L
        Joystick.button(6, DS4.getButtonPress(R1)); // R
        Joystick.button(7, DS4.getButtonPress(L2)); // ZL
        Joystick.button(8, DS4.getButtonPress(R2)); // ZR
        Joystick.button(9, DS4.getButtonPress(TOUCHPAD)); // -
        Joystick.button(10, DS4.getButtonPress(OPTIONS)); // +
        Joystick.button(11, DS4.getButtonPress(L3)); // LS
        Joystick.button(12, DS4.getButtonPress(R3)); // RS
        Joystick.button(13, DS4.getButtonPress(PS)); // Home
        Joystick.button(14, DS4.getButtonPress(SHARE)); // Capture
    }
    Joystick.send_now();
}
