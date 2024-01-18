#pragma once

template <uint8_t menuCount>
IntervalTimer MenuHandler<menuCount>::menuChangeTimer;

template <uint8_t menuCount>
long MenuHandler<menuCount>::previousMillisHold;

template <uint8_t menuCount>
uint16_t MenuHandler<menuCount>::holdingTime;

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentMenu;

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentValue[menuCount];

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::maxValue[menuCount];

template <uint8_t menuCount>
bool MenuHandler<menuCount>::previousState;

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::facePin;

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::menuPin;

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::resetPin;

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::holdPin;

template <uint8_t menuCount>
long MenuHandler<menuCount>::resetTime;

template <uint8_t menuCount>
int MenuHandler<menuCount>::pinNum;

template <uint8_t menuCount>
void MenuHandler<menuCount>::UpdateState() {
    long currentTime = millis();
    bool pinState = false;
    if (digitalRead(facePin)) {
        pinNum = 1;
        pinState = true;
    } 
    if (digitalRead(menuPin)) {
         pinNum = 2;
         pinState = true;
    } 
    if (digitalRead(resetPin)) {
         pinNum = 3;
         pinState = true;
    } 
    if (digitalRead(holdPin)) { 
        pinNum = 4;
        pinState = true;
    } 

    long timeOn = 0;

    if (currentTime > resetTime && currentValue[0] == 100) {
        currentValue[0] = 0;
    }
    
    if(!pinState && !previousState){//pin not pressed, not triggered -> reset time
        previousMillisHold = currentTime;
    }
    else if (!pinState && previousState){//pin not pressed, was triggered -> measure time
        timeOn = currentTime - previousMillisHold;
        previousState = false;
    }
    else if (pinState){//pin is pressed,
        previousState = true;
    }


    if(timeOn > 50 && !pinState){
        previousMillisHold = currentTime;
        switch(pinNum) {
            case 1: // advance face
                currentValue[currentMenu] += 1;
                if (currentValue[currentMenu] >= maxValue[currentMenu]) currentValue[currentMenu] = 0;
                break;
            case 2: // advance menu
                WriteEEPROM(currentMenu, currentValue[currentMenu]);
                currentMenu += 1;
                if (currentMenu >= menuCount) currentMenu = 0;
                break;
            case 3: // reset
                WriteEEPROM(currentMenu, currentValue[currentMenu]);
                currentMenu = 0;
                currentValue[0] = 0;
                break;
            case 4: // hold
                currentMenu = 0;
                currentValue[0] = 100;
                resetTime = currentTime + 300000;
        }
        pinNum = 0;
    }
}

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::ReadEEPROM(uint16_t index) {
    return EEPROM.read(index);
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::WriteEEPROM(uint16_t index, uint8_t value) {
    EEPROM.write(index, value);
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::Begin() {
    menuChangeTimer.begin(UpdateState, 1000);
}

template <uint8_t menuCount>
bool MenuHandler<menuCount>::Initialize(uint8_t facePin, uint8_t menuPin, uint8_t resetPin, uint8_t holdPin) {
    MenuHandler::previousState = false;

    pinMode(facePin, INPUT_PULLDOWN);
    pinMode(menuPin, INPUT_PULLDOWN);
    pinMode(resetPin, INPUT_PULLDOWN);
    pinMode(holdPin, INPUT_PULLDOWN);

    MenuHandler::facePin = facePin;
    MenuHandler::menuPin = menuPin;
    MenuHandler::resetPin = resetPin;
    MenuHandler::holdPin = holdPin;

    for (uint8_t i = 0; i < menuCount; i++) {
        currentValue[i] = ReadEEPROM(i);
    }

    return ReadEEPROM(menuCount + 1) != 255;
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::SetDefaultValue(uint16_t menu, uint8_t value) {
    if (menu >= menuCount) return;

    currentValue[menu] = value;

    WriteEEPROM(menu, value);
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::SetInitialized() {
    WriteEEPROM(menuCount + 1, 0);
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::SetMenuMax(uint8_t menu, uint8_t maxValue) {
    if (menu >= menuCount) return;

    MenuHandler::maxValue[menu] = maxValue;
}

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::GetMenuValue(uint8_t menu) {
    return currentValue[menu];
}

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::GetCurrentMenu() {
    return currentMenu;
}
