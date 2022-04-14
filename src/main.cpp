#include <Arduino.h>
#include "LedController.hpp"
#define DATA 11
#define CS 12
#define CLK 13
byte pins[] = {2, 3, 4, 5, 6, 7, 8, 9};
LedController lc = LedController(DATA, CLK, CS);

#define LED_GREEN_1 1
#define LED_YELLOW_1 2
#define LED_RED_1 4
#define LED_GREEN_2 8
#define LED_YELLOW_2 16
#define LED_RED_2 32
#define PEAT_1 64
#define PEAT_2 128

template <size_t N>
void output(const byte (&pinsArray)[N], const int num, const long delayTime)
{
    for (size_t i = 0; i < N; i++)
        digitalWrite(pinsArray[i], (num & (1 << i)) == 0 ? LOW : HIGH);

    delay(delayTime);
}

void TrafficLights(const byte green, const byte yellow, const byte redOther, const byte peatOther)
{
    output(pins, green | redOther | peatOther, 1500);
    for (byte i = 0; i < 3; i++)
    {
        output(pins, redOther | peatOther, 250);
        output(pins, redOther | green | peatOther, 250);
    }
    output(pins, redOther | yellow | peatOther, 2000);
}

void setup()
{
    for (auto &&item : pins)
        pinMode(item, OUTPUT);
}

void loop()
{
    TrafficLights(LED_GREEN_1, LED_YELLOW_1, LED_RED_2, PEAT_2);
    TrafficLights(LED_GREEN_2, LED_YELLOW_2, LED_RED_1, PEAT_1);
}