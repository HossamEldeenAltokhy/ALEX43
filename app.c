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

#define SLAVE1   0
#define SLAVE2   1


void select_slave(char slave_order);
int main(void) {
    // Static Design
    setpinOUT(PB,PB0);
    setpinOUT(PB,PB1);
    setpin(PB, PB0);
    setpin(PB, PB1);
    init_SPI(SPI_MASTER,0 );
    while (1) {
        // Dynamic Design
        select_slave(SLAVE1);
        SPI_write('A');//01000001
        
        select_slave(SLAVE2);
        SPI_write('B');//01000001

    }

    return 0;
}


void select_slave(char slave_order){
    if(slave_order == SLAVE1){
        setpin(PB, PB1);
        resetpin(PB, PB0);
    }else  if(slave_order == SLAVE2){
        setpin(PB, PB0);
        resetpin(PB, PB1);
    }
    else{
        
    }
}