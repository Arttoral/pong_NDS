#include "menu.h"


// Menu items array
struct menuItem items[] = {
    {"Start Game", 0},
    {"Reset", 1},
    {"Mode", 2},
    {"Bounce", 3}
};

// Global menu variables
int keys;
int itemCount = 3;
int cursor = 0;
bool selected = false;


int menuLogic(Rect *left, Rect *right, Ball *ball) {
    int choice = 0;

    // This goes through and if the item is selected, it performs the action    
    if(selected) {
        consoleClear();
        switch(cursor) {
            case 0:
                choice = 1;
                ball->vx = speed;
                ball->vy = speed;
                consoleClear();
                iprintf("\nGame Start!\n");
                iprintf("Press Y to cancel\n");
                for(int countdown = 120; countdown > 0; countdown--) {
                    swiWaitForVBlank();
                    scanKeys();
                    if(keysDown() & KEY_Y) {
                        choice = 0; 
                        break;
                    }
                }
                break;
            case 1:
                // Now these modify the ACTUAL game objects
                choice = 2;
                ball->x = SCREEN_WIDTH/2;
                ball->y = SCREEN_HEIGHT/2;
                speed = 2;
                left->y = (SCREEN_HEIGHT/2) - 24;
                right->y = (SCREEN_HEIGHT/2) - 24;
                consoleClear();
                iprintf("Resetting...\n");
                iprintf("Press A to cancel\n");
                break;
            case 2:
                // Show mode change message for 2 seconds or until B is pressed
                choice = 3;
                consoleClear();
                iprintf("Press X to increase speed, press Y to decrease.\n");
                iprintf("Press B to quit.\n");
                break;
        }
        selected = false; // reset selection after action

    } else {
        // Display normal menu when not selected
        for (int x = 0; x < itemCount; x++) {
            // Basically writes all the menu items to the screen
            char cursorChar = (x == cursor) ? '>' : ' ';
            iprintf("%c %s\n\n", cursorChar, items[x].name);
        }
    }

    return choice;
}

int menuUpDown(int keys, int cursor) {
    if (keys & KEY_UP) { // Changed to LEFT/RIGHT so that other keys can be used for gameplay. 
        cursor--;
        if (cursor < 0) {
            cursor = 2;
        }
    } else if (keys & KEY_DOWN) {
        cursor++;
        if (cursor > 2) {
            cursor = 0;
        }
    }
    return cursor;
}
