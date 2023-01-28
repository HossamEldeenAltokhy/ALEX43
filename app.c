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

// Timer0 _ Clock Selection Options
#define Timer0_OFF          0
#define Timer0_PRE_Non      1
#define Timer0_PRE_8        2
#define Timer0_PRE_64       3
#define Timer0_PRE_256      4
#define Timer0_PRE_1024     5
#define Timer0_Falling_Edge 6
#define Timer0_Rising_Edge  7


// Timer0 _ Modes
#define Timer0_Normal       0       // (WGM01 = 0, WGM00 = 0)
#define Timer0_CTC          1       // (WGM01 = 1, WGM00 = 0)
#define Timer0_PWM          2       // (WGM01 = 0, WGM00 = 1)
#define Timer0_FPWM         3       // (WGM01 = 1, WGM00 = 1)

// Timer0_OC0_Normal modes
#define Timer0_Normal_OC0_disconnect    0
#define Timer0_Normal_OC0_toggle        1
#define Timer0_Normal_OC0_clear         2
#define Timer0_Normal_OC0_set           3

// Timer0_OC0_PWM modes
#define Timer0_PWM_OC0_disconnect       0
#define Timer0_PWM_OC0_clear_set        2
#define Timer0_PWM_OC0_set_clear        3

// Timer0_OC0_FPWM modes
#define Timer0_FPWM_OC0_disconnect       0
#define Timer0_FPWM_OC0_clear_set        2
#define Timer0_FPWM_OC0_set_clear        3

#define DutyCycle_50                     50

void Timer0_select_CLK(char Clock_Select);
void Timer0_select_Mode(char Timer0_mode);
void Timer0_select_OC0_mode(char Timer0_OC0_mode);
void Timer0_enable_OVIE();
void Timer0_enable_OCIE();

void Timer0_set_DutyCycle(char DutyCycle_percentage);

void init_Timer0(char Timer0_mode,
        char Timer0_OC0_mode,
        char Timer0_OC0_DutyCycle,
        char Timer0_Prescalar
        );


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

void Timer0_select_CLK(char Clock_Select) {

    // TCCR0
    TCCR0 &= 0xF8; // 11111000
    TCCR0 |= Clock_Select;
}

void Timer0_select_Mode(char Timer0_mode) {
    switch (Timer0_mode) {

        case Timer0_Normal:// (WGM01 = 0, WGM00 = 0)
            TCCR0 &= ~(1 << WGM00);
            TCCR0 &= ~(1 << WGM01);
            break;
        case Timer0_CTC: // (WGM01 = 1, WGM00 = 0)
            TCCR0 &= ~(1 << WGM00);
            TCCR0 |= (1 << WGM01);
            break;
        case Timer0_PWM: // (WGM01 = 0, WGM00 = 1)
            TCCR0 |= (1 << WGM00);
            TCCR0 &= ~(1 << WGM01);
            break;
        case Timer0_FPWM:// (WGM01 = 1, WGM00 = 1)
            TCCR0 |= (1 << WGM00);
            TCCR0 |= (1 << WGM01);
            break;
        default:
            // None
            break;
    }
}

void Timer0_enable_OVIE(){
    TIMSK |= (1<<TOIE0);
}
void Timer0_enable_OCIE(){
    TIMSK |= (1<<OCIE0);
}

void Timer0_select_OC0_mode(char Timer0_OC0_mode){
    TCCR0 &= 0xCF;  // 11001111
    TCCR0 |= (Timer0_OC0_mode<<COM00);
}

void Timer0_set_DutyCycle(char DutyCycle_percentage){
    // DutyCycle = t1/t2*100 %   , t1-> High period, t2 -> Total period
    // DutyCycle = OCR0/255*100 %
    
    OCR0 = (100-DutyCycle_percentage)*255.0/100.0;
    
    
    
}

void init_Timer0(
        char Timer0_mode,   // nlknlkclkcne
        char Timer0_OC0_mode,  //kenlkenklfe
        char Timer0_OC0_DutyCycle,   // DutyCycle 0-100%, in case of (PWM or FPWM Only).
        char Timer0_Prescalar // 
        ){
    
    Timer0_select_Mode(Timer0_mode);
    Timer0_select_OC0_mode(Timer0_OC0_mode);
    if(Timer0_mode == Timer0_FPWM || Timer0_mode == Timer0_PWM){
    Timer0_set_DutyCycle(Timer0_OC0_DutyCycle);
    }
    Timer0_select_CLK(Timer0_Prescalar);
    
}