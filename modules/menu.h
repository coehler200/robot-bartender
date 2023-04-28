struct menuItem { //Store as linked list
	char* title;
	struct menuItem* parent;
	struct menuItem* children[16];
	int numChildren;
	void (*function)(void);
};

void __menuFuction0(void);
void __menuFuction1(void);

void __menuFuction0_0(void);
void __menuFuction0_1(void);
void __menuFuction0_2(void);
void __menuFuction0_3(void);
void __menuFuction0_4(void);
void __menuFuction0_5(void);

void __menuFuction1_0(void);
void __menuFuction1_1(void);
void __menuFuction1_2(void);
void __menuFuction1_3(void);
void __menuFuction1_4(void);
void __menuFuction1_5(void);
void __menuFuction1_6(void);
void __menuFuction1_7(void);

void __buildMenu(void);
void __appendMenuChild(struct menuItem* parent, struct menuItem* child);
void __setMenuItem(struct menuItem* item, char* title, void (*function)(void));
void __drawMenu(void);

void setupMenu(int* stateP);
void menuUpdate(void); //poll inputs and run animations or update display (called by systick)
void menuSelect(void); //called when user pushes the rotary encoder button
