/* 
 * File:   mspi.h
 * Author: hossa
 *
 * Created on 10 ??????, 2023, 09:42 ?
 */

#ifndef MSPI_H
#define	MSPI_H


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


#endif	/* MSPI_H */

