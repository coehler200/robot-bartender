#include "functions.h"
#include "lcd.h"
#include "analog.h"
#include <stdbool.h>

void intToString(char str[], int num){
	int rem, len = 0, endIndex = 0, n;

	n = num;
	while (n != 0){
		len++;
		n /= 10;
	}
	endIndex = len;
	
	if(num < 0){
		len++;
		num*=-1;
		str[0] = '-';
	}
	
	if(num == 0){
		len++;
		endIndex++;
	}
	
	for (int i = 0; i < endIndex; i++){
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = (char)(rem + '0');
	}
	str[len] = '\0';
}

void waitForCup(void){
	int numSuccesses = 0;
	
	clearLcd();
	writeLcdString("Waiting for Cup");
	
	while(numSuccesses < 100){
		if(readAnalogPin(0) < 0.01){
			numSuccesses++;
		}
	}
}
