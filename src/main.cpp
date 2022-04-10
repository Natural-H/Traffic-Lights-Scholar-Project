#include <Arduino.h>
#include "LedController.hpp"
#define DATA 11
#define CS 12
#define CLK 13

byte pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
LedController lc = LedController(DATA, CLK, CS);

template <size_t N>
void output(const byte (&pinsArray)[N], const int num, const long delayTime)
{
    for(int i = 0; i < N; i++) 
        digitalWrite(pinsArray[i], (num & (1 << i)) == 0 ? LOW : HIGH);
    
    delay(delayTime);
}

void setup()
{
    for (auto &&item : pins)
        pinMode(item, OUTPUT);
}

void loop()
{
}