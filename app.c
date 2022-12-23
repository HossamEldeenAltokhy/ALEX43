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
    setpinOUT(PA, test_led);
    setpinIN(PC, push_btn);
    // Turn off test_led.
    resetpin(PA, test_led);

    // Dynamic Design
    while (1) {

        if (readPin(PC, push_btn)) {
            setpin(PA, test_led);
        } else {
            resetpin(PA, test_led);
        }

    }

    return 0;
}
