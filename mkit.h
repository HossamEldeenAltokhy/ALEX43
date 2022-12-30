/* 
 * File:   mkit.h
 * Author: hossa
 *
 * Created on 30 ??????, 2022, 09:52 ?
 */

#ifndef MKIT_H
#define	MKIT_H
#include <xc.h>

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

#endif	/* MKIT_H */

