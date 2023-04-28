#include "rotenc.h"

static int current = 0;
static int last = 0;

//Call with interupt on chA (PA4)
void rotEncEvent(void){
	if(!(GPIOA->IDR & GPIO_IDR_IDR10)){
		current++;
	}
	else{
		current--;
	}
}

int rotEncDiff(void){
	int diff = last - current;
	last = current;
	if(diff > 0){
		return 1;
	}else if(diff < 0){
		return -1;
	}else{
		return 0;
	}
}
