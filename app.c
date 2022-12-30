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
#include "mkit.h"
#include <stdlib.h>

#define LCD_DATA    PA
#define LCD_CONTROL PB
#define LCD_RS      PB7
#define LCD_RW      PB0
#define LCD_EN      PB2

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

char str[] = "Hello World!";
int main(void) {
    // Static Design

    lcd_init();
    int x = 102;

    // Dynamic Design
    while (1) {
        lcd_cmd(LCD_cmd_return_home);
        lcd_data_num(x--);
        _delay_ms(500);
    }
    return 0;
}

void lcd_data_str(char * pData) {

    for (int index = 0; pData[index] != '\0'; index++) {
        lcd_data(pData[index]);
    }
}

void lcd_enable() {
    setpin(LCD_CONTROL, LCD_EN);
    _delay_ms(10);
    resetpin(LCD_CONTROL, LCD_EN);
}

/**
 * This function is to initialize LCD device to Microcontroller
 */
void lcd_init() {
    // PIN Configuration

    // set LCD_DATA as OUT
    setportOUT(LCD_DATA);
    // set RS as output
    setpinOUT(LCD_CONTROL, LCD_RS);
    // set RW as output
    setpinOUT(LCD_CONTROL, LCD_RW);
    _delay_ms(5);
    resetpin(LCD_CONTROL, LCD_RW); // (RW =0)
    // set EN as output
    setpinOUT(LCD_CONTROL, LCD_EN);
    _delay_ms(5);
    resetpin(LCD_CONTROL, LCD_EN); // (EN =0)



    // LCD initialization ...

    lcd_cmd(LCD_cmd_CLEAR); // CLEAR command
    lcd_cmd(LCD_cmd_ENTRY_MODE);
    lcd_cmd(LCD_cmd_8bit_2lines_MODE);
    lcd_cmd(LCD_cmd_D_ON_C_OFF);

    _delay_ms(50);

}

void lcd_data(char data) {

    // put data on DATA BUS
    setDataPort(LCD_DATA, data);
    // select LCD Data Register   (RS =1)
    setpin(LCD_CONTROL, LCD_RS);
    // Enable
    lcd_enable();

}

void lcd_cmd(char cmd) {

    // put data on DATA BUS
    setDataPort(LCD_DATA, cmd);
    // select LCD Instruction Register   (RS =0)
    resetpin(LCD_CONTROL, LCD_RS);
    // Enable
    lcd_enable();

}

void lcd_data_num(int num){
    char str[11];
    itoa(num, str, 10);
    lcd_data_str(str);
}