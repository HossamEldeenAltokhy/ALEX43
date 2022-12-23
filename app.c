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
            setpin(PA, led0);
            setpin(PA, led1);
            setpin(PA, led2);
            setpin(PA, led3);
        } else {
            resetpin(PA, led0);
            resetpin(PA, led1);
            resetpin(PA, led2);
            resetpin(PA, led3);
        }

// Case push button 1
        if (isPressed(PD, push_btn1)) {
            setpin(PA, led4);
            setpin(PA, led5);
            setpin(PA, led6);
            setpin(PA, led7);
        } else {
            resetpin(PA, led4);
            resetpin(PA, led5);
            resetpin(PA, led6);
            resetpin(PA, led7);
        }

    }

    return 0;
}
