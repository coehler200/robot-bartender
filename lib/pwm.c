#include "pwm.h"

void setupPWM3(uint16_t arr){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	TIM3->CR1 |= TIM_CR1_CEN; // Enable Timer3
	
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; // PWM mode 1 - CH 1
	TIM3->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE; // Preload Enable, Fast Enable - CH 1
	
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1; // PWM mode 1 - CH 2
	TIM3->CCMR1 |= TIM_CCMR1_OC2PE | TIM_CCMR1_OC2FE; // Preload Enable, Fast Enable - CH 2
	
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; // PWM mode 1 - CH 3
	TIM3->CCMR2 |= TIM_CCMR2_OC3PE | TIM_CCMR2_OC3FE; // Preload Enable, Fast Enable - CH 3
	
	TIM3->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1; // PWM mode 1 - CH 4
	TIM3->CCMR2 |= TIM_CCMR2_OC4PE | TIM_CCMR2_OC4FE; // Preload Enable, Fast Enable - CH 4
	
	TIM3->CCER |= TIM_CCER_CC1E; // Enable CH1
	TIM3->CCER |= TIM_CCER_CC2E; // Enable CH2
	TIM3->CCER |= TIM_CCER_CC3E; // Enable CH3
	TIM3->CCER |= TIM_CCER_CC4E; // Enable CH4
	
	TIM3->EGR |= TIM_EGR_UG; // Reinitialize the counter
	TIM3->PSC = 0x095F; // Divide 24 MHz by 2400 (PSC+1), PSC_CLK= 10000 Hz, 1 count = 0.1 ms
	TIM3->ARR = arr; // 100 counts = 10 ms or 100 Hz
}

void setupPWM4(uint16_t arr){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	TIM4->CR1 |= TIM_CR1_CEN; // Enable Timer3
	
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; // PWM mode 1 - CH 1
	TIM4->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE; // Preload Enable, Fast Enable - CH 1
	
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1; // PWM mode 1 - CH 2
	TIM4->CCMR1 |= TIM_CCMR1_OC2PE | TIM_CCMR1_OC2FE; // Preload Enable, Fast Enable - CH 2
	
	TIM4->CCER |= TIM_CCER_CC1E; // Enable CH1
	TIM4->CCER |= TIM_CCER_CC2E; // Enable CH2
	TIM4->CCER |= TIM_CCER_CC3E; // Enable CH3
	TIM4->CCER |= TIM_CCER_CC4E; // Enable CH4
	
	TIM4->EGR |= TIM_EGR_UG; // Reinitialize the counter
	TIM4->PSC = 0x095F; // Divide 24 MHz by 2400 (PSC+1), PSC_CLK= 10000 Hz, 1 count = 0.1 ms
	TIM4->ARR = arr; // 100 counts = 10 ms or 100 Hz
}

void setPWM3_1(uint16_t ccr){
	TIM3->CCR1 = ccr; // 50 counts = 5 ms = 50% duty cycle
	TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer3
}

void setPWM3_2(uint16_t ccr){
	TIM3->CCR2 = ccr; // 50 counts = 5 ms = 50% duty cycle
	TIM3->CR1	|= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer3
}

void setPWM3_3(uint16_t ccr){
	TIM3->CCR3 = ccr; // 50 counts = 5 ms = 50% duty cycle
	TIM3->CR1	|= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer3
}

void setPWM3_4(uint16_t ccr){
	TIM3->CCR4 = ccr; // 50 counts = 5 ms = 50% duty cycle
	TIM3->CR1	|= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer3
}

void setPWM4_1(uint16_t ccr){
	TIM4->CCR1 = ccr; // 50 counts = 5 ms = 50% duty cycle
	TIM4->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer4
}

void setPWM4_2(uint16_t ccr){
	TIM4->CCR2 = ccr; // 50 counts = 5 ms = 50% duty cycle
	TIM4->CR1	|= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer4
}


void setPWM4_3(uint16_t ccr){
	TIM4->CCR3 = ccr; // 50 counts = 5 ms = 50% duty cycle
	TIM4->CR1	|= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer4
}


void setPWM4_4(uint16_t ccr){
	TIM4->CCR4 = ccr; // 50 counts = 5 ms = 50% duty cycle
	TIM4->CR1	|= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer4
}
