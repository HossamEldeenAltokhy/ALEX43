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
#include "mUART.h"
#include "mspi.h"
#include <avr/interrupt.h>

// My address
#define address_Enabled_GC    0x07  // 00000111
#define address_Disabled_GC   0x06  // 00000110

// My slaves
#define SLA_W    0xAE  //10100000 
#define SLA_R    0xAF  //10100001


    


void init_TWI(char address_GC, char Baudrate);

void TWI_start();
void TWI_stop();
char TWI_read_status();
void TWI_call(char SLA);
void TWI_write(char data);
char TWI_read();
void TWI_ack();
void TWI_wait();

void EEPROM_write(short address, char data);
char EEPROM_read(short address);

//ISR(TWI_vect) {
//    char status_code = TWI_read_status();
//    switch (status_code) {
//        case 0x08:
//            TWI_call(SLA_R);
//            break;
//        case 0x18:
//            TWI_write('A');
//            break;
//        case 0x40:
//            TWI_ack();
//            break;
//        case 0x50:
//            PORTA = TWI_read();
//            TWI_stop();
//            break;
//        case 0x28:
//            TWI_stop();
//            break;
//    }
//    TWCR |= (1 << TWINT);
//
//}

char status_code;

int main(void) {
    // Static Design
    kit_setup();
    lcd_init();

    init_TWI(address_Enabled_GC, 0);
    _delay_ms(1000);




    EEPROM_write(0x0019, 'Z');
    _delay_ms(1000);
    
    lcd_data(EEPROM_read(0x0019));
            






    while (1) {
        // Dynamic Design


    }

    return 0;
}

void init_TWI(char address_GC, char Baudrate) {
    // TWCR  (NOT used)
    //    TWCR |= (1 << TWIE);

    TWAR = address_GC;
    // TWBR >> 255
    TWBR = 3;

    // TWSR (NOT used)
}

void TWI_start() {

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);

}

void TWI_stop() {

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

}

void TWI_ack() {

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

}

char TWI_read_status() {
    char status_code = TWSR & 0xF8;
    return status_code;
}

void TWI_call(char SLA) {
    //?????????
    TWDR = SLA;
    // start Transmission
    TWCR = (1 << TWINT) | (1 << TWEN);
}

void TWI_write(char data) {
    // data to be sent
    TWDR = data;
    // start Transmission
    TWCR = (1 << TWINT) | (1 << TWEN);
}

char TWI_read() {
    return TWDR;
}

void TWI_wait() {
    while (!(TWCR & (1 << TWINT)));
}

void EEPROM_write(short address, char data) {
    TWI_start();
    TWI_wait();
    status_code = TWI_read_status();
    if (status_code == 0x08) {
        TWI_call(SLA_W);
        TWI_wait();
        status_code = TWI_read_status();
        if (status_code == 0x18) { // 0x20
            TWI_write((char) address>>8); // Address  Byte 1
            TWI_wait();
            status_code = TWI_read_status();
            if (status_code == 0x28) {
                TWI_write((char) address); // Address  Byte 0
                TWI_wait();
                status_code = TWI_read_status();
                if (status_code == 0x28) {
                    TWI_write(data); // Data Stored at Location No 1
                    TWI_wait();
                    status_code = TWI_read_status();
                    if (status_code == 0x28) {
                        TWI_stop();

                    }
                    TWI_stop();


                }

            }
        }
    }

}
char EEPROM_read(short address){
    char received_data = '0';
        TWI_start();
    TWI_wait();
    status_code = TWI_read_status();
    if (status_code == 0x08) {
        TWI_call(SLA_W);
        TWI_wait();
        status_code = TWI_read_status();
        if (status_code == 0x18) {
            TWI_write((char) address>>8);
            TWI_wait();
            status_code = TWI_read_status();
            if (status_code == 0x28) {
                TWI_write((char) address);
                TWI_wait();
                status_code = TWI_read_status();
                if (status_code == 0x28) {
                    // Repeated Start
                    TWI_start();
                    TWI_wait();
                    status_code = TWI_read_status();
                    if (status_code == 0x10) {
                        // 
                        TWI_call(SLA_R);

                        TWI_wait();
                        status_code = TWI_read_status();
                        if (status_code == 0x40) {
                            TWI_ack();
                            TWI_wait();
                            status_code = TWI_read_status();
                            if (status_code == 0x50) {

                                received_data = TWI_read();

                                TWI_stop();
                            }
                        }
                    }
                }
            }

        }
    }
    
    return received_data;
}