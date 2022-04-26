#include <Arduino.h>
#include "LedControl.h"
byte pins[] = {2, 3, 4};               // G1 -> 2  Y1 -> 3  R1 -> 4
LedControl lc1 = LedControl(10, 9, 8); // DIN1 -> 10 CLK1 -> 9  CS1 -> 8

byte Stop[] = {0x38, 0x38, 0x10, 0x38, 0x54, 0x10, 0x28, 0x44};
byte Go[] = {0x18, 0x18, 0x08, 0x3c, 0x4a, 0x18, 0x28, 0x44};

inline void drawImage(LedControl &lc, byte bitmap[8]) {
    for (size_t i = 0; i < 8; i++)
        lc.setColumn(0, i, bitmap[i]);
}

template <size_t N>
inline void output(byte (&pinsArray)[N], byte num, unsigned long delayTime = 0) {
    for (size_t i = 0; i < N; i++)
        digitalWrite(pinsArray[i], (num & (1 << i)) == 0); // Active on zero

    delay(delayTime);
}

void setup() {
    for (auto &&item : pins)
        pinMode(item, OUTPUT);

    lc1.setIntensity(0, 8);
    lc1.shutdown(0, false);
}

void loop() {
    drawImage(lc1, Stop);
    output(pins, 1 << 0, 1500);
    for (byte i = 0; i < 3; i++) {
        output(pins, 0, 250);
        output(pins, 1 << 0, 250);
    }
    output(pins, 1 << 1, 3000);
    drawImage(lc1, Go);
    output(pins, 1 << 2);
    for (byte i = 0; i < 4; i++) {
        tone(5, 6000, 325);
        delay(325);
        tone(5, 1150, 325);
        delay(700);
    }
    for (byte i = 0; i < 3; i++) {
        tone(5, 2500, 150);
        delay(250);
    }
}