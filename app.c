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


ISR(ADC_vect) {
    int result = 0;
    // Read ADC DATA Register
    result = ADCL;
    result |= (ADCH << 8);
    int val = result * 4.8828125;

    lcd_clear();
    lcd_data_num(val);
    lcd_data('m');
    lcd_data('V');
    _delay_ms(50);

    
    ADC_START();
}

int main(void) {
    // Static Design
    kit_setup();
    lcd_init();
    init_ADC(CH3_CH1_1, Ref_AVCC, PRE_128);

    sei();
                                                  
    ADC_START();
    // Dynamic Design
    while (1) {

        if (isPressed(BTN0)) {
            LED_on(LED0);
        } else {
            LED_off(LED0);
        }


    }

    return 0;
}

