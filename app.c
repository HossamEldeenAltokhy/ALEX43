/*
 * File:   app.c
 * Author: hossa
 *
 * Created on 16 ??????, 2022, 11:57 ?
 */

#define F_CPU 16000000UL
#include <xc.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "DIO.h"
#include "mADC.h"
#include "mlcd.h"
#include "mkit.h"
#include "mTimer.h"


ISR(TIMER0_OVF_vect){
    // Timer Overflow
}
ISR(TIMER0_COMP_vect){
    // Compare Match
}
int main(void) {
    // Static Design
    setportOUT(PA);
    kit_setup();
    setpinOUT(PB, 3);
    
    init_Timer0(Timer0_Normal,
            Timer0_Normal_OC0_disconnect,
            DutyCycle_50,
            Timer0_PRE_1024);
    OCR0 = 200;
    Timer0_enable_OVIE();
    Timer0_enable_OCIE();
    
    sei();
    while (1) {
        // Dynamic Design
        
        if(isPressed(BTN2)){
            OCR0 += 10;
            _delay_ms(500);
        }
        if(isPressed(BTN1)){
            OCR0 -= 10;
            _delay_ms(500);
        }

    }

    return 0;
}
