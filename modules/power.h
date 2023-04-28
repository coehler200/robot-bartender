#include "stm32f10x.h"
#include "../lib/gpio.h"
#include <stdbool.h>

void powerPump(bool en);
void powerValve1(bool en);
void powerValve2(bool en);
void powerValve3(bool en);
void powerValve4(bool en);

void togglePump(void);
void toggleValve1(void);
void toggleValve2(void);
void toggleValve3(void);
void toggleValve4(void);

void powerOff(void);
