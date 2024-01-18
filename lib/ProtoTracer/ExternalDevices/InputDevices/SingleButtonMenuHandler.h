#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <IntervalTimer.h>

template <uint8_t menuCount>
class MenuHandler {
private:
    static IntervalTimer menuChangeTimer;
    static long previousMillisHold;
    static uint16_t holdingTime;
    static uint8_t currentMenu;
    static uint8_t currentValue[menuCount];
    static uint8_t maxValue[menuCount];
    static bool previousState;
    static uint8_t facePin;
    static uint8_t menuPin;
    static uint8_t resetPin;
    static uint8_t holdPin;
    static long resetTime;
    static int pinNum;

    static void UpdateState();
    static uint8_t ReadEEPROM(uint16_t index);
    static void WriteEEPROM(uint16_t index, uint8_t value);

public:
    static void Begin();
    static bool Initialize(uint8_t facePin, uint8_t menuPin, uint8_t resetPin, uint8_t holdPin);
    static void SetDefaultValue(uint16_t menu, uint8_t value);
    static void SetInitialized();
    static void SetMenuMax(uint8_t menu, uint8_t maxValue);
    static uint8_t GetMenuValue(uint8_t menu);
    static uint8_t GetCurrentMenu();
};

#include "SingleButtonMenuHandler.tpp"