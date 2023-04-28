#include "menu.h"
#include "../lib/rotenc.h"
#include <stddef.h>
#include "../lib/sounds.h"
#include "../lib/lcd.h"
#include "power.h"
#include "prime.h"
#include "dispense.h"

static struct menuItem* head;
static struct menuItem* current;
static int menuIndex;
static int* statePtr;

static struct menuItem menuItemRoot;
static struct menuItem menuItemDispense;
static struct menuItem menuItemOptions;
static struct menuItem menuItem0_Back;
static struct menuItem menuItem0_DrinkA;
static struct menuItem menuItem0_DrinkB;
static struct menuItem menuItem0_DrinkC;
static struct menuItem menuItem0_DrinkD;
static struct menuItem menuItem0_DrinkE;
static struct menuItem menuItem1_Back;
static struct menuItem menuItem1_Prime;
static struct menuItem menuItem1_Pump;
static struct menuItem menuItem1_Valve1;
static struct menuItem menuItem1_Valve2;
static struct menuItem menuItem1_Valve3;
static struct menuItem menuItem1_Valve4;
static struct menuItem menuItem1_AllOff;

void __menuFuction0(void){ //Dispense
	current = &menuItemDispense;
	menuIndex = 0;
}

void __menuFuction1(void){ //Options
	current = &menuItemOptions;
	menuIndex = 0;
}

void __menuFuction0_0(void){ //Back
	current = head;
	menuIndex = 0;
}

void __menuFuction0_1(void){ //Drink A
	dispenseBegin(statePtr, 10, 5, 4, 9);
}

void __menuFuction0_2(void){ //Drink B
	dispenseBegin(statePtr, 5, 15, 7, 4);
}

void __menuFuction0_3(void){ //Drink C
	dispenseBegin(statePtr, 10, 10, 10, 20);
}

void __menuFuction0_4(void){ //Drink D
	dispenseBegin(statePtr, 5, 6, 7, 8);
}

void __menuFuction0_5(void){ //Drink E
	dispenseBegin(statePtr, 9, 10, 11, 12);
}

void __menuFuction1_0(void){ //Back
	current = head;
	menuIndex = 0;
}

void __menuFuction1_1(void){ //Prime
	primeBegin(statePtr);
}

void __menuFuction1_2(void){ //Pump
	togglePump();
}

void __menuFuction1_3(void){ //Valve1
	toggleValve1();
}

void __menuFuction1_4(void){ //Valve2
	toggleValve2();
}

void __menuFuction1_5(void){ //Valve3
	toggleValve3();
}

void __menuFuction1_6(void){ //Valve4
	toggleValve4();
}

void __menuFuction1_7(void){ //All Off
	powerOff();
}

void __buildMenu(void){
	__setMenuItem(&menuItemRoot, "Root", NULL);
	menuItemRoot.parent = NULL;
	head = &menuItemRoot;
	
	__setMenuItem(&menuItemDispense, "Dispense", __menuFuction0);
	__appendMenuChild(&menuItemRoot, &menuItemDispense);
	
	__setMenuItem(&menuItemOptions, "Options", __menuFuction1);
	__appendMenuChild(&menuItemRoot, &menuItemOptions);
	
	__setMenuItem(&menuItem0_Back, "Back", __menuFuction0_0);
	__appendMenuChild(&menuItemDispense, &menuItem0_Back);
	
	__setMenuItem(&menuItem0_DrinkA, "Drink A", __menuFuction0_1);
	__appendMenuChild(&menuItemDispense, &menuItem0_DrinkA);
	
	__setMenuItem(&menuItem0_DrinkB, "Drink B", __menuFuction0_2);
	__appendMenuChild(&menuItemDispense, &menuItem0_DrinkB);
	
	__setMenuItem(&menuItem0_DrinkC, "Drink C", __menuFuction0_3);
	__appendMenuChild(&menuItemDispense, &menuItem0_DrinkC);
	
	__setMenuItem(&menuItem0_DrinkD, "Drink D", __menuFuction0_4);
	__appendMenuChild(&menuItemDispense, &menuItem0_DrinkD);
	
	__setMenuItem(&menuItem0_DrinkE, "Drink E", __menuFuction0_5);
	__appendMenuChild(&menuItemDispense, &menuItem0_DrinkE);
	
	__setMenuItem(&menuItem1_Back, "Back", __menuFuction1_0);
	__appendMenuChild(&menuItemOptions, &menuItem1_Back);
	
	__setMenuItem(&menuItem1_Prime, "Prime System", __menuFuction1_1);
	__appendMenuChild(&menuItemOptions, &menuItem1_Prime);
	
	__setMenuItem(&menuItem1_Pump, "Toggle Pump", __menuFuction1_2);
	__appendMenuChild(&menuItemOptions, &menuItem1_Pump);
	
	__setMenuItem(&menuItem1_Valve1, "Toggle Valve 1", __menuFuction1_3);
	__appendMenuChild(&menuItemOptions, &menuItem1_Valve1);
	
	__setMenuItem(&menuItem1_Valve2, "Toggle Valve 2", __menuFuction1_4);
	__appendMenuChild(&menuItemOptions, &menuItem1_Valve2);
	
	__setMenuItem(&menuItem1_Valve3, "Toggle Valve 3", __menuFuction1_5);
	__appendMenuChild(&menuItemOptions, &menuItem1_Valve3);
	
	__setMenuItem(&menuItem1_Valve4, "Toggle Valve 4", __menuFuction1_6);
	__appendMenuChild(&menuItemOptions, &menuItem1_Valve4);
	
	__setMenuItem(&menuItem1_AllOff, "All Off", __menuFuction1_7);
	__appendMenuChild(&menuItemOptions, &menuItem1_AllOff);
}

void __appendMenuChild(struct menuItem* parent, struct menuItem* child){
	parent->children[parent->numChildren] = child;
	parent->numChildren++;
	child->parent = parent;
}

void __setMenuItem(struct menuItem* item, char* title, void (*function)(void)){
	item->title = title;
	item->function = function;
}

void __drawMenu(void){
	clearLcd();
	
	sendLcdChar('>');
	writeLcdString(current->children[menuIndex]->title);
	
	if(current->numChildren > menuIndex+1){
		setLcdCursorPos(1, 0);
		sendLcdChar(' ');
		writeLcdString(current->children[menuIndex+1]->title);
	}
}

void setupMenu(int* stateP){
	__buildMenu();
	menuIndex = 0;
	current = head;
	statePtr = stateP;
	__drawMenu();
}

void menuUpdate(void){
	int inputDiff = rotEncDiff();
	
	if(*statePtr == 0){ //Menu State
		if(inputDiff != 0){
			playInteraction();
			
			menuIndex+=inputDiff;
			if(menuIndex >= current->numChildren){
				menuIndex = 0;
			}else if(menuIndex < 0){
				menuIndex = current->numChildren-1;
			}
			
			__drawMenu();
		}
	}
	else if(*statePtr == 1){ //Dispense State
		
	}
	else if(*statePtr == 2){ //Prime State
		
	}
	else if(*statePtr == -1){ //Return from function
		*statePtr = 0;
		__drawMenu();
	}
}

void menuSelect(void){
	playInteraction2();
	
	if(*statePtr == 0){ //Menu State
		current->children[menuIndex]->function();
		if(*statePtr == 0){
			__drawMenu();
		}
	}
	else if(*statePtr == 1){ //Dispense State
		dispenseCancel();
	}
	else if(*statePtr == 2){ //Prime State
		primeNext();
	}
}
