#include "interupt.h"

//calls "void SysTick_Handler(void)" on tick
void setupSystickISR(uint32_t load){
	SysTick->CTRL = 0x0; 
	SysTick->VAL = 0x0;
	SysTick->LOAD = load;
	SysTick->CTRL = 0x7;
}

void stopSystickISR(void){
	SysTick->CTRL = 0x0;
}

//calls "void EXTI2_IRQHandler(void)" on falling edge PB2
void setupPB2ISR(void){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI2_PB;
	EXTI->IMR |= EXTI_IMR_MR2;
	EXTI->FTSR |= EXTI_FTSR_TR2;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_8;
}

//calls "void EXTI4_IRQHandler(void)" on falling edge PA4
void setupPA4ISR(void){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[0] |= AFIO_EXTICR2_EXTI4_PA;
	EXTI->IMR |= EXTI_IMR_MR4;
	EXTI->FTSR |= EXTI_FTSR_TR4;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_10;
}
