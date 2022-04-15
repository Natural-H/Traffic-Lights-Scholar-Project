#include <Arduino.h>
#include "LedControl.h"
byte pins[] = {2, 3, 4, 5, 6, 7}; // G1 -> 2  Y1 -> 3  R1 -> 4 -- G2 -> 5  Y2 -> 6  R2 -> 7
LedControl lc1 = LedControl(10, 9, 8); // DIN1 -> 10 CLK1 -> 9  CS1 -> 8
LedControl lc2 = LedControl(13, 12, 11); // DIN2 -> 13  CLK2 -> 12  CS2 -> 11

byte Stop[] = {0x38, 0x38, 0x10, 0x38, 0x54, 0x10, 0x28, 0x44};
byte Go[] = {0x18, 0x18, 0x08, 0x3c, 0x4a, 0x18, 0x28, 0x24};

void drawImage(LedControl &lc, byte bitmap[8]) {
    for (int i = 0; i < 8; i++)
        lc.setColumn(0, i, bitmap[i]);
}

template <size_t N>
void output(byte (&pinsArray)[N], int num, long delayTime) {
    for (size_t i = 0; i < N; i++)
        digitalWrite(pinsArray[i], (num & (1 << i)) == 0 ? LOW : HIGH);

    delay(delayTime);
}

void TrafficLights(byte greenPin, byte yellowPin, byte redOtherPin, LedControl &peat, LedControl &peatOther) {
    drawImage(peat, Stop);
    drawImage(peatOther, Go);
    output(pins, greenPin | redOtherPin, 1500);
    for (byte i = 0; i < 3; i++) {
        output(pins, redOtherPin, 250);
        output(pins, redOtherPin | greenPin, 250);
    }
    output(pins, redOtherPin | yellowPin, 2000);
}

void setup() {
    for (auto &&item : pins)
        pinMode(item, OUTPUT);

    lc1.setIntensity(0, 8);
    lc1.shutdown(0, false);
    lc2.setIntensity(0, 8);
    lc2.shutdown(0, false);
}

void loop() {
    TrafficLights(1 << 0, 1 << 1, 1 << 5, lc1, lc2); // 1 << n is an equivalent to 2^n and pins
    TrafficLights(1 << 3, 1 << 4, 1 << 2, lc2, lc1); // are in powers of 2, so 1 << n is the nth pin
}