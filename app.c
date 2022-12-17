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


void setportOUT(char portName);
void setportIN(char portName);

void setpinOUT(char portName, char pinNum);
void setpinIN(char portName, char pinNum);

// Special
char readPin(char portName, char pinNum);

int main(void) {
    // Static Design
    //PORTA as output
//    DDRA |= (1 << test_led);
    setpinOUT('A', test_led);
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

void setportOUT(char portName){
        switch(portName){
        case 'A':
            DDRA = 0xFF;
            break;
        case 'B':
            DDRB = 0xFF;
            break;
        case 'D':
            DDRD = 0xFF;
            break;
        case 'C':
            DDRC = 0xFF;
            break;
    }
}

void setpinOUT(char portName, char pinNum){
    switch(portName){
        case 'A':
            DDRA |= (1<<pinNum);
            break;
        case 'B':
            DDRB |= (1<<pinNum);
            break;
        case 'D':
            DDRD |= (1<<pinNum);
            break;
        case 'C':
            DDRC |= (1<<pinNum);
            break;
    }
}