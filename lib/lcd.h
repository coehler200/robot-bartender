#include "stm32f10x.h"
#include "clock.h" //delay functions
#include "gpio.h"
#include "functions.h"

#define GPIOB_LCD_EN 11
#define GPIOB_LCD_RS 10

#define GPIOB_LCD_D7 15
#define GPIOB_LCD_D6 14
#define GPIOB_LCD_D5 13
#define GPIOB_LCD_D4 12

#define LCD_LINE0 (uint8_t)0x00
#define LCD_LINE1 (uint8_t)0x40

#define LCD_OPTMASK_NONE (uint8_t)0x08
#define LCD_OPTMASK_DISPON (uint8_t)0x0C
#define LCD_OPTMASK_CURSON (uint8_t)0x0A
#define LCD_OPTMASK_BLNKON (uint8_t)0x09

#define LCD_ENTMASK_DIRRIGHT (uint8_t)0x06
#define LCD_ENTMASK_SHIFT (uint8_t)0x05

#define LCD_SHIFT_DIS_LEFT (uint8_t)0x18
#define LCD_SHIFT_DIS_RIGHT (uint8_t)0x1C
#define LCD_SHIFT_CUR_LEFT (uint8_t)0x10
#define LCD_SHIFT_CUR_RIGHT (uint8_t)0x14

void setupLcd(void);
void sendLcdHalfCommand(uint8_t);
void sendLcdCommand(uint8_t);
void sendLcdChar(uint8_t);

void clearLcd(void);
void setLcdCursorPos(int row, int col);
void setLcdCustomChar(uint8_t, uint8_t*);

void writeLcdString(char*);
void writeLcdInt(int i);
