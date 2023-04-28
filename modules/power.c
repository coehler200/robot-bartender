#include "power.h"
#include "../lib/pwm.h"

#define PUMP_SPEED 25

static bool pumpState = false;

void powerPump(bool en){
	pumpState = en;
	
	if(en == true){
		setPWM3_2(PUMP_SPEED);
	}else{
		setPWM3_2(0);
	}
}

void powerValve1(bool en){
	setPin(GPIOB, 8, en);
}

void powerValve2(bool en){
	setPin(GPIOB, 5, en);
}

void powerValve3(bool en){
	setPin(GPIOA, 11, en);
}

void powerValve4(bool en){
	setPin(GPIOA, 12, en);
}

void togglePump(void){
	powerPump(!pumpState);
}

void toggleValve1(void){
	invertPin(GPIOB, 8);
}

void toggleValve2(void){
	invertPin(GPIOB, 5);
}

void toggleValve3(void){
	invertPin(GPIOA, 11);
}

void toggleValve4(void){
	invertPin(GPIOA, 12);
}

void powerOff(void){
	setPWM3_2(0);
	setPin(GPIOB, 8, false);
	setPin(GPIOB, 5, false);
	setPin(GPIOA, 11, false);
	setPin(GPIOA, 12, false);
}
