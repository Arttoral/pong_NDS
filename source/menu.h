#ifndef MENU_H
#define MENU_H

#include <nds.h>
#include <stdio.h>

// Menu item structure
struct menuItem {
    const char* name;
    int count;
};

// Global menu variables
extern struct menuItem items[];
extern int keys;
extern int itemCount;
extern int cursor;
extern bool selected;

// Function declarations
int menuLogic();
int menuUpDown(int keys, int cursor);


#endif // MENU_H