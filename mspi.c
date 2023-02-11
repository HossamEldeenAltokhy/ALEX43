
#include <xc.h>
#include "mspi.h"

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