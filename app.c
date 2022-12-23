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

#define PA    0
#define PB    1
#define PC    2
#define PD    3


void setportOUT(char portName);
void setportIN(char portName);

void setpinOUT(char portName, char pinNum);
void setpinIN(char portName, char pinNum);

// Special
char readPin(char portName, char pinNum);

void setpin(char portName, char pinNum);
void resetpin(char portName, char pinNum);

int main(void) {
    // Static Design
    //PORTA as output
    //    DDRA |= (1 << test_led);
    setpinOUT(PA, test_led);
    //    DDRC &= ~(1 << push_btn); // Reset 
    setpinIN(PC, push_btn);
    // Turn off test_led.
    //    PORTA &= ~(1 << test_led);
    setpin(PA, test_led);
    // Dynamic Design
    while (1) {

        // if (PINC & (1 << push_btn)) {
        if (readPin(PC, push_btn)) {
            //PORTA |= (1 << test_led);
            setpin(PA, test_led);
        } else {
            //PORTA &= ~(1 << test_led);
            resetpin(PA, test_led);

        }


    }

    return 0;
}

char readPin(char portName, char pinNum) {

    switch (portName) {
        case PA:
            return (PINA & (1 << pinNum)) ? 1 : 0;
            break;
        case PB:
            return (PINB & (1 << pinNum)) ? 1 : 0;
            break;
        case PC:
            return (PINC & (1 << pinNum)) ? 1 : 0;
            break;
        case PD:
            return (PIND & (1 << pinNum)) ? 1 : 0;
            break;
        default:
            return 0;
    }


}

void setportOUT(char portName) {
    switch (portName) {
        case PA:
            DDRA = 0xFF;
            break;
        case PB:
            DDRB = 0xFF;
            break;
        case PD:
            DDRD = 0xFF;
            break;
        case PC:
            DDRC = 0xFF;
            break;
    }
}

void setportIN(char portName) {
    switch (portName) {
        case PA:
            DDRA = 0x00;
            break;
        case PB:
            DDRB = 0x00;
            break;
        case PD:
            DDRD = 0x00;
            break;
        case PC:
            DDRC = 0x00;
            break;
    }
}

void setpinOUT(char portName, char pinNum) {
    switch (portName) {
        case PA:
            DDRA |= (1 << pinNum);
            break;
        case PB:
            DDRB |= (1 << pinNum);
            break;
        case PC:
            DDRD |= (1 << pinNum);
            break;
        case PD:
            DDRC |= (1 << pinNum);
            break;
    }
}

void setpinIN(char portName, char pinNum) {
    switch (portName) {
        case PA:
            DDRA &= ~(1 << pinNum);
            break;
        case PB:
            DDRB &= ~(1 << pinNum);
            break;
        case PD:
            DDRD &= ~(1 << pinNum);
            break;
        case PC:
            DDRC &= ~(1 << pinNum);
            break;
    }
}

void setpin(char portName, char pinNum) {
    //    PORTA |= (1<<N)
    switch (portName) {
        case PA:
            PORTA |= (1 << pinNum);
            break;
        case PB:
            PORTB |= (1 << pinNum);
            break;
        case PC:
            PORTC |= (1 << pinNum);
            break;
        case PD:
            PORTD |= (1 << pinNum);
            break;
    }

}

void resetpin(char portName, char pinNum) {
    //PORTA &= ~(1<<N);
    switch (portName) {
        case PA:
            PORTA &= ~(1 << pinNum);
            break;
        case PB:
            PORTB &= ~(1 << pinNum);
            break;
        case PC:
            PORTC &= ~(1 << pinNum);
            break;
        case PD:
            PORTD &= ~(1 << pinNum);
            break;
    }
}