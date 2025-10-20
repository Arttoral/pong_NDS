#ifndef MENU_H
#define MENU_H

#include <nds.h>
#include <stdio.h>
#include "sprites.h"

// Menu item structure
struct menuItem {
    const char* name;
    int count;
};


// Global menu variables
extern int leftScore;
extern int rightScore;
extern struct menuItem items[];
extern int keys;
extern int itemCount;
extern int cursor;
extern bool selected;
extern int speed;

// Function declarations
int menuLogic(Rect* left, Rect* right, Ball* ball);
int menuUpDown(int keys, int cursor);


#endif // MENU_H