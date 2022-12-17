/*
 * File:   app.c
 * Author: hossa
 *
 * Created on 16 ??????, 2022, 11:57 ?
 */

#define F_CPU 16000000UL
#include <xc.h>
#include <util/delay.h>

int main(void) {
    // Static Design
    //Data Direction Register
    DDRA = 0xFF; // All pins as outputs
    PORTA = 0x01; // PA0 = ON
    char key = 0;
    // Dynamic Design
    while (1) {

        _delay_ms(500);
        if (!key) {
            PORTA *= 2;
        }
        else{
            PORTA /= 2;
        }

        if (PORTA == 0x80) {
            key = 1;
        }
        if(PORTA == 0x01){
            key = 0;
        }
    }

    return 0;
}

// Bitwise Masking
/*
 DDRA |= (1<<n);
 DDRA &= ~(1<<n);
 DDRA ^= (1<<n);
 */
