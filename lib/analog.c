#include "analog.h"

void setup_ADC1(void){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1->CR2 |= ADC_CR2_ADON;	
}

double readAnalogPin(unsigned int in){
	ADC1->SQR3 |= (in&0xFFFF);
	ADC1->CR2 |= ADC_CR2_ADON;
	
	while((ADC1->SR & ADC_SR_EOC) == 0x0){}
		
	return (double)ADC1->DR/0x0fff;
}
