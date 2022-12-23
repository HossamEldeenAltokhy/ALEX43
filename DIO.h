/* 
 * File:   DIO.h
 * Author: hossa
 *
 * Created on 23 ??????, 2022, 09:52 ?
 */

#ifndef DIO_H
#define	DIO_H

#define test_led   0
#define push_btn   0

#define PA    0
#define PB    1
#define PC    2
#define PD    3

void setportOUT(char portName);
void setportIN(char portName);

void setpinOUT(char portName, char pinNum);
void setpinIN(char portName, char pinNum);

// Special
char readPin(char portName, char pinNum);

void setpin(char portName, char pinNum);
void resetpin(char portName, char pinNum);


#endif	/* DIO_H */

