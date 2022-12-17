/*
 * File:   app.c
 * Author: hossa
 *
 * Created on 16 ??????, 2022, 11:57 ?
 */

#define F_CPU 16000000UL
#include <xc.h>
#include <util/delay.h>

#define test_led   0
#define push_btn   0

int main(void) {
    // Static Design
    //PORTA as output
    DDRA |= (1 << test_led);
    DDRC &= ~(1 << push_btn); // Reset 

    // Turn off test_led.
    PORTA &= ~(1 << test_led);
    // Dynamic Design
    while (1) {

        if (PINC & (1 << push_btn)) {
            PORTA |= (1 << test_led);
        } else {
            PORTA &= ~(1 << test_led);
        }


    }

    return 0;
}


