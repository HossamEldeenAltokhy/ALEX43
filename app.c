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

#define CH0     0   // 00000
#define CH1     1   // 00001
#define CH2     2   // 00011
#define CH3     3   // 00100
#define CH4     4   
#define CH5     5
#define CH6     6
#define CH7     7   // 00111

#define Ref_AVCC   1
#define Ref_2_56   3
#define Ref_AREF   0

#define PRE_2      0
#define PRE_4      2
#define PRE_8      3
#define PRE_16     4
#define PRE_32     5
#define PRE_64     6
#define PRE_128    7



void selectCH(char CH){
    ADMUX &= 0xE0; //11100000
    ADMUX |= CH;
}
void selectREF(char REF){
    ADMUX &= 0x3F; // 00111111
    ADMUX |= (REF<<6);
}

void selectFREQ(char freq){
    ADCSRA &= 0xF8; // 11111000
    ADCSRA |= freq;
}

void ADC_EN(){
    ADCSRA |= (1<<ADEN);
}
void ADC_START(){
    ADCSRA |= (1<<ADSC);
}

int main(void) {
    // Static Design
    lcd_init();
    // Select CH
    // ADMUX ( CH Selection)
    selectCH(CH1);  // 00000000
    
    // Select Ref
    selectREF(Ref_AVCC);
    // Select Freq
    selectFREQ(PRE_128);
    // Enable ADC
    ADC_EN();
    // *** Operate .....
    int result =0 ;
    // Dynamic Design
    while (1) {

        ADC_START();
       // Check FLAG  ADIF
        while(!(ADCSRA & (1<<ADIF)));
        // Read ADC DATA Register
//        PORTC = ADCL;
//        PORTD = ADCH;
           
        result = ADCL;
        result |= (ADCH<<8);
        
        lcd_clear();
        lcd_data_num(result); //*4.8828125
        lcd_data('\'');
        lcd_data('C');
        _delay_ms(50);

    }

    return 0;
}

