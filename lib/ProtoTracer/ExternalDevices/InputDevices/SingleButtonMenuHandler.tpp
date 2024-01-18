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
uint8_t MenuHandler<menuCount>::pin;

template <uint8_t menuCount>
bool MenuHandler<menuCount>::holdingState;

template <uint8_t menuCount>
bool MenuHandler<menuCount>::previousState;

template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::pressCount = 0;

template<uint8_t menuCount>
long MenuHandler<menuCount>::lastPress = 0;

template <uint8_t menuCount>
void MenuHandler<menuCount>::UpdateState() {
    long currentTime = millis();
        bool pinState = digitalRead(pin);
        long timeOn = 0;

        if (currentTime > lastPress + 300000 && currentValue[0] == 100) {
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

        if(timeOn > holdingTime && !pinState){
            previousMillisHold = currentTime;

            WriteEEPROM(currentMenu, currentValue[currentMenu]);

            if (timeOn > holdingTime * 4) {
                currentMenu = 0;
                currentValue[0] = 0;
            } else {
                currentMenu += 1;
                if (currentMenu >= menuCount) currentMenu = 0;
            }
        } else if(timeOn > 50 && !pinState){
            pressCount++;
            lastPress = currentTime;
            
            previousMillisHold = currentTime;

            currentValue[currentMenu] += 1;
            if (currentValue[currentMenu] >= maxValue[currentMenu]) currentValue[currentMenu] = 0;
        }

        if (currentTime - lastPress > 200)
        {
            if (pressCount == 2) {
                currentMenu = 0;
                currentValue[0] = 100;
            }
            pressCount = 0;
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
bool MenuHandler<menuCount>::Initialize(uint8_t pin, uint16_t holdingTime) {
    MenuHandler::holdingState = true;

    MenuHandler::previousState = false;

    pinMode(pin, INPUT_PULLDOWN);

    MenuHandler::pin = pin;
    MenuHandler::holdingTime = holdingTime;

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
