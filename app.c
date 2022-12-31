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

#define B0   0
#define B1   1
#define mled0   0
#define mled1   1

char str_led0_is_on[] = "LED0 is ON";
char str_led1_is_on[] = "LED1 is ON";
char str_led0_is_off[] = "LED0 is OFF";
char str_led1_is_off[] = "LED1 is OFF";

void init_pushBTNS();
void init_allLeds();
char led0_status;
char led1_status;

int main(void) {
    // Static Design
    init_allLeds();
    init_pushBTNS();

    lcd_init();




    // Dynamic Design
    while (1) {
        if (readPin(PC, B0)) {
            // LED0 is ON
            if (!led0_status) {
                setpin(PD, mled0);
                lcd_clear();
                lcd_data_str(str_led0_is_on);
                led0_status = 1;
            }

        } else {
            // LED0 is OFF
            if (led0_status) {
                resetpin(PD, mled0);
                lcd_clear();
                lcd_data_str(str_led0_is_off);
                led0_status = 0;
            }
            
        }

        if (readPin(PC, B1)) {
            // LED1 is ON
           if (!led1_status) {
                setpin(PD, mled1);
                lcd_clear();
                lcd_data_str(str_led1_is_on);
                led1_status = 1;
            }
        } else {
            // LED1 is OFF
            if (led1_status) {
                resetpin(PD, mled1);
                lcd_clear();
                lcd_data_str(str_led1_is_off);
                led1_status = 0;
            }
        }
    }
    return 0;
}

void init_pushBTNS() {
    setpinIN(PC, B0);
    setpinIN(PC, B1);
}

void init_allLeds() {
    setpinOUT(PD, mled0);
    setpinOUT(PD, mled1);

    resetpin(PD, mled0);
    resetpin(PD, mled1);
}