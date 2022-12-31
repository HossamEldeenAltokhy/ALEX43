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
#define LCD_CONTROL PB
#define LCD_RS      PB2
#define LCD_RW      PB1
#define LCD_EN      PB0

// Commands
/**
 * 
 */
#define LCD_cmd_CLEAR            0x01
#define LCD_cmd_ENTRY_MODE       0x06   
#define LCD_cmd_8bit_2lines_MODE 0x38
#define LCD_cmd_D_ON_C_OFF       0x0C

#define LCD_cmd_return_home      0x02

void lcd_init();
void lcd_data(char data);
void lcd_data_str(char * pData);


void lcd_cmd(char cmd);
void lcd_enable();
void lcd_data_num(int num);
void lcd_clear();
#endif	/* MLCD_H */

