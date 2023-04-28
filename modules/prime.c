#include "prime.h"
#include "../lib/functions.h"

static int state = 0;
static int* statePtr;

void primeBegin(int* stateP){
	statePtr = stateP;
	*statePtr = 2;
	state = 1;
	
	waitForCup();
	
	__primeState();
}

void primeNext(void){
	state++;
	__primeState();
}

void __primeState(void){
	clearLcd();
	
	if(state >= 5){
		powerOff();
		*statePtr = -1; 
	}
	else{
		writeLcdString("Priming... #");
		writeLcdInt(state);
		setLcdCursorPos(1, 0);
		writeLcdString("Press when done");
		
		powerOff();
		switch(state){
			case 1:
				powerValve1(true);
				powerPump(true);	
				break;
			case 2:
				powerValve2(true);
				powerPump(true);	
				break;
			case 3:
				powerValve3(true);
				powerPump(true);	
				break;
			case 4:
				powerValve4(true);
				powerPump(true);	
				break;
		}
	}
}
