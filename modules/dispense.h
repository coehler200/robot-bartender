#include "power.h"
#include "../lib/lcd.h"
#include "../lib/clock.h"
#include "../lib/analog.h"
#include "../lib/sounds.h"
#include "../lib/interupt.h"

void dispenseBegin(int* stateP, int d1, int d2, int d3, int d4);
void dispenseCancel(void);
void dispenseUpdate(void);
void __dispenseNext(void);
