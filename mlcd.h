/* 
 * File:   mlcd.h
 * Author: hossa
 *
 * Created on 31 ??????, 2022, 08:52 ?
 */

#ifndef MLCD_H
#define	MLCD_H
#include <xc.h>
#include "DIO.h"

#define LCD_DATA    PA
#define LCD_DATA_PORT PORTA
#define LCD_CONTROL PB
#define LCD_RS      PB1
#define LCD_RW      PB2
#define LCD_EN      PB3

// To enable 8bit mode uncomment next line, To enable 4 bit mode comment next line.
//#define LCD_8bit_MODE  

#ifdef LCD_8bit_MODE 
#define LCD_cmd_MODE 0x38
#else
#define LCD_cmd_MODE 0x02
#endif



#define LCD_cmd_CLEAR            0x01
#define LCD_cmd_ENTRY_MODE       0x06  
#define LCD_cmd_D_ON_C_OFF       0x0C
#define LCD_cmd_return_home      0x02

void lcd_init();
void lcd_data(char data);
void lcd_data_str(char * pData);
void lcd_goto(char row, char coln);

void lcd_cmd(char cmd);
void lcd_enable();
void lcd_data_num(int num);
void lcd_clear();
#endif	/* MLCD_H */

