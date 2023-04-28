#include "dispense.h"
#include "../lib/functions.h"

static int* statePtr;
static int state = 0;
static int d1Amt;
static int d2Amt;
static int d3Amt;
static int d4Amt;
static int remaining;
static int max;

void dispenseBegin(int* stateP, int d1, int d2, int d3, int d4){
	statePtr = stateP;
	*statePtr = 1;
	state = 0;
	d1Amt = d1;
	d2Amt = d2;
	d3Amt = d3;
	d4Amt = d4;
	
	waitForCup();
	
	__dispenseNext();
}

void dispenseCancel(void){
	stopSystickISR();
	powerOff();
	
	if(state >= 5){
		playDone();
	}
	
	state = -1;
	*statePtr = -1;
}

void dispenseUpdate(void){
	if(state != 0){
		int percent;
		remaining--;
		
		percent = 100 - (int)((1.0*remaining/max)*100);
		setLcdCursorPos(1,0);
		for(int i=0; i<(percent/8); i++){
			sendLcdChar(0xFF);
		}
		
		setLcdCursorPos(1,12);
		sendLcdChar('%');
		writeLcdInt(percent);
		
		if(remaining <= 0){
			__dispenseNext();
		}
	}
}

void __dispenseNext(void){
	stopSystickISR();
	
	state++;
	
	if(state >= 5){
		dispenseCancel(); //end
	}else{
		clearLcd();
		writeLcdString("Dispensing #");
		writeLcdInt(state);
		
		powerOff();
		switch(state){
			case 1:
				powerValve1(true);
				powerPump(true);	
				remaining = d1Amt;
				break;
			case 2:
				powerValve2(true);
				powerPump(true);	
				remaining = d2Amt;
				break;
			case 3:
				powerValve3(true);
				powerPump(true);	
				remaining = d3Amt;
				break;
			case 4:
				powerValve4(true);
				powerPump(true);
				remaining = d4Amt;
				break;
		}
		
		max = remaining;
		
		setupSystickISR(0xB71B00);
	}
}
