#ifndef MENU_H_
#define MENU_H_

#include <inttypes.h>
#include "suit.h"

#define MENU_COUNT 28
#define MAX_SUBMENUS 10
#define MAX_NAME 20

typedef struct _Menu {
	char* name;
	uint8_t submenusCount;
	InputType inputType;
	KeySignature keySigValue;
	Note* noteValue;
	uint8_t* intValue;
	void (*command)(uint8_t);
	char* (*valueString)(struct _Menu*);
	struct _Menu* previousMenu;
	struct _Menu* submenus[MAX_SUBMENUS];
} Menu;

char* Menu_getNoteString(Menu* menu);
char* Menu_getIntString(Menu* menu);
void Menu_setKeySignature(uint8_t value);
void Menu_init(Settings *setS, SuitState *suitS);
void Menu_displayCurrentMenu();
uint8_t Menu_isAtRootMenu();
void Menu_goToParentMenu();
void Menu_setMenu(Menu* menu);
void Menu_moveDown();
void Menu_moveUp();
void Menu_select();
void Menu_waitForInput(Menu* noteValue);

#endif /* MENU_H_ */
