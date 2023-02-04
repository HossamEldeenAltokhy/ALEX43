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

#define SS   4  
#define MOSI 5
#define MISO 6
#define SCK  7

#define SPI_MASTER   1
#define SPI_SLAVE    0

void init_SPI(char MASTER, char SPI_CLK);
void SPI_write(char data);
char SPI_read();
void SPI_INT_Enable();

int main(void) {
    // Static Design

    init_SPI(SPI_MASTER,0 );
    while (1) {
        // Dynamic Design

        SPI_write('A');

    }

    return 0;
}

void init_SPI(char MASTER, char SPI_CLK) {

    if (MASTER) {
        // Pin Configuration for Master Mode
        DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);
        // Master Mode
        SPCR |= (1 << SPE) | (1 << MSTR);
        SPCR |= (1 << SPR1) | (1 << SPR0);
    } else {
        // Pin Configuration for Slave Mode
        DDRB |= (1<<MISO);
        // Slave Mode
        SPCR |= (1 << SPE);
    }

}
void SPI_write(char data){
    SPDR = data;
    while(!( SPSR &(1<<SPIF)));
}
char SPI_read(){
    while(!( SPSR &(1<<SPIF)));
    return SPDR;
}
void SPI_INT_Enable(){
    SPCR |= (1<<SPIE);
}