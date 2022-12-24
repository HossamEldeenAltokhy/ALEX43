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

int main(void) {
    // Static Design
    //setup LEDS
    setportOUT(PA);
    // Setup push buttons
    setpinIN(PC, push_btn0);
    setpinIN(PD, push_btn1);
    // Turn off All LEDS.
    resetport(PA);

    // Dynamic Design
    while (1) {
        // Case push button 0

        if (isPressed(PC, push_btn0)) {
            PORTA++;
            _delay_ms(500);
        } else {

        }

        // Case push button 1
        if (isPressed(PD, push_btn1)) {
            PORTA--;
            _delay_ms(500);

        } else {

        }

    }

    return 0;
}
