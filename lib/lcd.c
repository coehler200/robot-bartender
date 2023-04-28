#include "lcd.h"

void setupLcd(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //GPIOB pins 10-15 must be set to output push/pull before this
	
	delayMS(30);
	sendLcdHalfCommand(0x30);
	delayMS(10);
	sendLcdHalfCommand(0x30);
	delayMS(5);
	sendLcdHalfCommand(0x30);
	
	sendLcdHalfCommand(0x20); //Switch to 4-bit mode
	
	sendLcdCommand(0x2C); //Set num of lines and font
	sendLcdCommand(0x08); //Display Off
	sendLcdCommand(0x01); //Display Clear
	sendLcdCommand(LCD_ENTMASK_DIRRIGHT); //Entry Mode Set

	sendLcdCommand(LCD_OPTMASK_DISPON); //Display On
}

void sendLcdHalfCommand(uint8_t data){
	setPin(GPIOB, GPIOB_LCD_EN, true);
	setPin(GPIOB, GPIOB_LCD_RS, false);
	
	setPin(GPIOB, GPIOB_LCD_D7, data&0x80);
	setPin(GPIOB, GPIOB_LCD_D6, data&0x40);
	setPin(GPIOB, GPIOB_LCD_D5, data&0x20);
	setPin(GPIOB, GPIOB_LCD_D4, data&0x10);
	
	delayMS(1);
	
	setPin(GPIOB, GPIOB_LCD_EN, false);
	
	delayMS(5);
}

void sendLcdCommand(uint8_t data){
	sendLcdHalfCommand(data);
	sendLcdHalfCommand((uint8_t)(data << 0x4));
}

void sendLcdChar(uint8_t data){
	setPin(GPIOB, GPIOB_LCD_EN, true);
	setPin(GPIOB, GPIOB_LCD_RS, true);
	
	setPin(GPIOB, GPIOB_LCD_D7, data&0x80);
	setPin(GPIOB, GPIOB_LCD_D6, data&0x40);
	setPin(GPIOB, GPIOB_LCD_D5, data&0x20);
	setPin(GPIOB, GPIOB_LCD_D4, data&0x10);
	
	delayMS(1);
	
	setPin(GPIOB, GPIOB_LCD_EN, false);
	
	delayMS(5);
	setPin(GPIOB, GPIOB_LCD_EN, true);
	
	setPin(GPIOB, GPIOB_LCD_D7, data&0x08);
	setPin(GPIOB, GPIOB_LCD_D6, data&0x04);
	setPin(GPIOB, GPIOB_LCD_D5, data&0x02);
	setPin(GPIOB, GPIOB_LCD_D4, data&0x01);
	
	delayMS(1);
	
	setPin(GPIOB, GPIOB_LCD_EN, false);
	
	delayMS(5);
}

void clearLcd(void){
	sendLcdCommand(0x01);
}

void setLcdCursorPos(int row, int col){
	uint8_t cmd = 0x80;
	
	if(row < 0 || row > 1 || col < 0 || col > 31){
		cmd |= LCD_LINE0;
	}
	else{
		if(row == 0){
			cmd |= LCD_LINE0;
		}
		else{
			cmd |= LCD_LINE1;
		}
		
		cmd |= col&0x0F;
	}
	sendLcdCommand(cmd);
}

void setLcdCustomChar(uint8_t charIndex, uint8_t* charData){
	uint8_t addrCmd = 0x40 | (uint8_t)(charIndex << 3);
	sendLcdCommand(addrCmd);
	
	for(int i=0; i<8; i++){
		sendLcdChar(charData[i]);
	}
}

void writeLcdString(char* text){
	int index = 0;
	while(text[index] != '\0'){
		sendLcdChar(text[index]);
		index++;
	}
}

void writeLcdInt(int i){
	char snum[10];
	
	intToString(snum, i);
	
	writeLcdString(snum);
}
