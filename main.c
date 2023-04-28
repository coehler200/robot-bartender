#include "stm32f10x.h"
#include "lib/clock.h"
#include "lib/gpio.h"
#include "lib/lcd.h"
#include "lib/pwm.h"
#include "lib/interupt.h"
#include "lib/rotenc.h"
#include "lib/analog.h"
#include "lib/functions.h"

#include "modules/menu.h"
#include "modules/power.h"
#include "modules/dispense.h"

//0: Menu; 1: Dispense; 2: Prime
static int state = 0;

void SysTick_Handler(void);
void EXTI2_IRQHandler(void);
void EXTI4_IRQHandler(void);

int main(void){	
	sysClkInit();
	startClk_gpioA();
	startClk_gpioB();
	setupGPIO();
	setupLcd();
	setup_ADC1();
	setupPWM3(100);
	setPWM3_1(0);
	powerOff();
	
	//Startup Screen
	writeLcdString("Robot Bartender");
	setLcdCursorPos(1, 0);
	writeLcdString("V1.0 Cameron O");
	delayMS(4000);
	clearLcd();
	
	setupMenu(&state);
	
	//Start the ISRs after all other setup is done
	//setupSystickISR(0xB71B00); //B71B00
	setupPB2ISR();
	setupPA4ISR();
	
	while(1){
		menuUpdate();
	}
}

void SysTick_Handler(void){
	dispenseUpdate();
}

void EXTI2_IRQHandler(void){
	EXTI->PR |= EXTI_PR_PR2;
	menuSelect();
}

void EXTI4_IRQHandler(void){
	EXTI->PR |= EXTI_PR_PR4;
	rotEncEvent();
}
