#include "stm32f10x.h"
#include <stdbool.h>

void startClk_gpioA(void);
void startClk_gpioB(void);
void startClk_gpioC(void);
void startClk_gpioD(void);

void setupGPIO(void);
bool readPin(GPIO_TypeDef*, int);
void setPin(GPIO_TypeDef*, int, bool);
void invertPin(GPIO_TypeDef*, int);

uint8_t read4Bits(void);
