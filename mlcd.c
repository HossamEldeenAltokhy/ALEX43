#define F_CPU 16000000UL
#include "mlcd.h"
#include <stdlib.h>
#include <util/delay.h>

void lcd_clear(){
    lcd_cmd(LCD_cmd_CLEAR);
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