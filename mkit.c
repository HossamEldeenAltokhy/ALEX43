#include "DIO.h"
#include "mkit.h"

void kit_setup() {
    init_BTNs();
    init_LEDs();
    init_Buzzer();
    init_Relay();
}

void init_Buzzer() {
    // IO Configurations.
    setpinOUT(PA, Buzzer);
    // Buzzer reset.
    Buzzer_off();
}

void Buzzer_on() {
    setpin(PA, Buzzer);
}

void Buzzer_off() {
    resetpin(PA, Buzzer);
}

void init_Relay() {
    // IO Configurations.
    setpinOUT(PA, Relay);
    // Buzzer reset.
    Relay_off();
}

void Relay_on() {
    setpin(PA, Relay);
}

void Relay_off() {
    resetpin(PA, Relay);
}

void init_LEDs() {
    // IO Configurations
    setpinOUT(PC, LED0);
    setpinOUT(PC, LED1);
    setpinOUT(PD, LED2);
    // reset LEDs
    LED_off(LED0);
    LED_off(LED1);
    LED_off(LED2);
}

void LED_on(char LED_number) {
    switch (LED_number) {
        case LED0:
            setpin(PC, LED0);
            break;
        case LED1:
            setpin(PC, LED1);
            break;
        case LED2:
            setpin(PD, LED2);
            break;
        case ALL_LEDs:
            setpin(PC, LED0);
            setpin(PC, LED1);
            setpin(PD, LED2);
            break;
    }
}

void LED_off(char LED_number) {
    switch (LED_number) {
        case LED0:
            resetpin(PC, LED0);
            break;
        case LED1:
            resetpin(PC, LED1);
            break;
        case LED2:
            resetpin(PD, LED2);
            break;
        case ALL_LEDs:
            resetpin(PC, LED0);
            resetpin(PC, LED1);
            resetpin(PD, LED2);
            break;
    }
}

void init_BTNs() {
    // IO Configurations
    setpinIN(PB, BTN0);
    setpinIN(PD, BTN1);
    setpinIN(PD, BTN2);
}

char isPressed(char BTN_number) {

    switch (BTN_number) {
        case BTN0:
            return readPin(PB, BTN0);
            break;
        case BTN1:
            return readPin(PD, BTN1);
            break;
        case BTN2:
            return readPin(PD, BTN2);
            break;
        default:
            return 0;
    }


}