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

#include "mlcd.h"
#include "mkit.h"

#define Rising_Edge  3   // 0b00000011
#define Falling_Edge 2   // 0b00000010
#define Any_Edge     1   // 0b00000001
#define Low_Level    0   // 0b00000000



void init_INT0(char INT0_mode);
char letter = 0 ;
char str[]  ="INT0 is ON";

ISR(INT0_vect){
    lcd_clear();
    lcd_data_str(str);
//    _delay_ms(500);
}


int main(void) {
    // Static Design
    kit_setup();
    
    lcd_init();

    

    init_INT0(Any_Edge);
    //Enable for Global Interrupt Flag
    sei();
    
    // Dynamic Design
    while (1) {
        
//        if(isPressed(BTN2)){
//            lcd_data_str(str);
//        }

        while (1)
            lcd_data(letter++);

    }

    return 0;
}


void init_INT0(char INT0_mode) {
    // Select Interrupt Mode (Sense Control)
    switch (INT0_mode) {
        case Rising_Edge:
            //            ISC01 = 1, ISC00 =1
            MCUCR |= (1<<ISC00);
            MCUCR |= (1<<ISC01);
            break;
        case Falling_Edge:
            //            ISC01 = 1, ISC00 =0
            MCUCR &= ~(1 << ISC00);
            MCUCR |= (1 << ISC01);
            break;
        case Any_Edge:
            //            ISC01 = 0, ISC00 =1
            MCUCR |= (1 << ISC00);
            MCUCR &= ~(1 << ISC01);
            break;
        case Low_Level:
            //            ISC01 = 0, ISC00 =0
            MCUCR &= ~(1 << ISC00);
            MCUCR &= ~(1 << ISC01);
            break;
        default:
            break;
    }
    // Enable for INT0 (Individual Interrupt Enable)
    GICR |= (1<<INT0);
}

void init_INT1(char INT1_mode) {
    switch (INT1_mode) {
        case Rising_Edge:
            //            ISC11 = 1, ISC10 =1
            MCUCR |= (1<<ISC10);
            MCUCR |= (1<<ISC11);
            break;
        case Falling_Edge:
            //            ISC11 = 1, ISC10 =0
            MCUCR &= ~(1 << ISC10);
            MCUCR |= (1 << ISC11);
            break;
        case Any_Edge:
            //            ISC11 = 0, ISC10 =1
            MCUCR |= (1 << ISC10);
            MCUCR &= ~(1 << ISC11);
            break;
        case Low_Level:
            //            ISC11 = 0, ISC10 =0
            MCUCR &= ~(1 << ISC10);
            MCUCR &= ~(1 << ISC11);
            break;
        default:
            break;
    }
    
    GICR |= (1<<INT1);
}



////////////////////////
void init_INT0_(char INT0_mode){
    MCUCR &= ~(3<<0);
    MCUCR |= INT0_mode; // R=11,F=10,L=00,A=01
   // 0bxxxxxxxx | 0b00000011 = 0bxxxxxx11
}
void init_INT1_(char INT1_mode){
    MCUCR &= ~(3<<2);
    MCUCR |= (INT1_mode<<2); // R=11,F=10,L=00,A=01
   // 0bxxxxxxxx | 0b00000011 = 0bxxxxxx11
}
//////////////////////////////////



void init_INT2(char INT2_mode){
    if(INT2_mode == Falling_Edge){
        MCUCSR &= ~(1<<ISC2);
    }else if( INT2_mode == Rising_Edge){
        MCUCSR |= (1<<ISC2);
    }else{
        // Nothing
    }
    
    GICR |= (1<<INT2);
}