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

#include "mlcd.h"
#include "mkit.h"

/**
 * 
 * **Keypad
 * 
 * OUTPUT PINS: PORTC (0,1,2)
 * INPUT PINS : PORTD (4,5,6,7)
 * 
 */

char str[] = "Clicked!";
char str1[] = "L1 Clicked!";
char str2[] = "L2 Clicked!";
char str3[] = "L3 Clicked!";
char str4[] = "L4 Clicked!";
void keypad_set_all_on();
void keypad_reset_all_on();
void keypad_scan();
char keypad_activator = 1;

int main(void) {
    // Static Design
    lcd_init();
    // keypad io configuration
    setportOUT(PC);
    setportIN(PD);
    // delay
    _delay_ms(5);


    keypad_set_all_on();


   
    // Dynamic Design
    while (1) {
        
        keypad_scan();
    
    }
    return 0;
}
void keypad_scan(){
            keypad_set_all_on();
            
            while (PIND && keypad_activator ) {
            
            if (PIND & 0b00010000) {
                // Line 1
                keypad_reset_all_on();
                setpin(PC, 0);
                if (PIND & 0b00010000) {
                    lcd_data('3');
                    break;
                } else {
                    keypad_reset_all_on();
                    setpin(PC, 1);
                    if (PIND & 0b00010000) {
                        lcd_data('2');
                        break;
                    } else {
                        keypad_reset_all_on();
                        setpin(PC, 2);
                        if (PIND & 0b00010000) {
                            lcd_data('1');
                            break;
                        }
                    }
                }
            } else if (PIND & 0b00100000) {
                // Line 2
                keypad_reset_all_on();
                setpin(PC, 0);
                if (PIND & 0b00100000) {
                    lcd_data('6');
                    break;
                } else {
                    keypad_reset_all_on();
                    setpin(PC, 1);
                    if (PIND & 0b00100000) {
                        lcd_data('5');
                        break;
                    } else {
                        keypad_reset_all_on();
                        setpin(PC, 2);
                        if (PIND & 0b00100000) {
                            lcd_data('4');
                            break;
                        }
                    }
                }
            } else if (PIND & 0b01000000) {
                // Line 3
                lcd_data_str(str3);
            } else if (PIND & 0b10000000) {
                // Line 4
                lcd_data_str(str4);
            } else {
                // Nothing
            }

        } 
            _delay_ms(200);
}

void keypad_set_all_on() {
    setpin(PC, 0);
    setpin(PC, 1);
    setpin(PC, 2);
    _delay_ms(5);
}

void keypad_reset_all_on() {
    resetpin(PC, 0);
    resetpin(PC, 1);
    resetpin(PC, 2);
}