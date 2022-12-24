/*
 * File:   app.c
 * Author: hossa
 *
 * Created on 16 ??????, 2022, 11:57 ?
 */

#define F_CPU 16000000UL
#include <xc.h>
#include <util/delay.h>
#include "DIO.h"


#define LED0   PC2  // 2
#define LED1   PC7  // 7
#define LED2   PD3  // 3

#define BTN0   PB0   
#define BTN1   PD6
#define BTN2   PD2

#define Relay  PA2
#define Buzzer PA3

#define ALL_LEDs  10

// Buzzer functions
void init_Buzzer();
void Buzzer_on();
void Buzzer_off();
// Relay functions
void init_Relay();
void Relay_on();
void Relay_off();
// Buttons functions
void init_BTNs();
char isPressed(char BTN_number);
// LEDS functions
void init_LEDs();
void LED_on(char LED_number);
void LED_off(char LED_number);
// Kit setup functions
void kit_setup();

int main(void) {
    // Static Design
    kit_setup();
    _delay_ms(500);
    // Dynamic Design
    while (1) {
        // LED0
        if(isPressed(BTN0)){
            LED_on(LED0);
        }else{
            LED_off(LED0);
        }
        // LED1
        if(isPressed(BTN1)){
            LED_on(LED1);
        }else{
            LED_off(LED1);
        }
        // LED2
        if(isPressed(BTN2)){
            LED_on(LED2);
        }else{
            LED_off(LED2);
        }
    }
    return 0;
}

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
    _delay_ms(50);
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