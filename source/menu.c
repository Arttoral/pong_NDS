#include "menu.h"

// Menu items array
struct menuItem items[] = {
    {"Start Game", 0},
    {"Reset", 1},
    {"Mode", 2},
    {"Mode: Slow\n\n",  3}, // Added a non-selectable header for Mode

};

// Global menu variables
int keys;
int itemCount = 3;
int cursor = 0;
bool selected = false;


int menuLogic() {
    int choice = 0;

    // This goes through and if the item is selected, it performs the action    
    if(selected) {
        consoleClear();
        switch(cursor) {
            case 0:
                // Show start game message for 3 seconds or until B is pressed
                for(int countdown = 180; countdown > 0; countdown--) { // 3 seconds at 60fps
                    consoleClear();
                    iprintf("Starting Game...\n");
                    iprintf("Press B to cancel\n");
                    swiWaitForVBlank();
                    scanKeys();
                    if(keysDown() & KEY_B) break;
                }
                choice = 1;
                break;
            case 1:
                // Show reset message for 2 seconds or until B is pressed
                for(int countdown = 120; countdown > 0; countdown--) { // 2 seconds at 60fps
                    consoleClear();
                    iprintf("Resetting...\n");
                    iprintf("Press B to cancel\n");
                    swiWaitForVBlank();
                    scanKeys();
                    if(keysDown() & KEY_B) break;
                }
                choice = 2;
                break;
            case 2:
                // Show mode change message for 2 seconds or until B is pressed
                for(int countdown = 120; countdown > 0; countdown--) { // 2 seconds at 60fps
                    consoleClear();
                    iprintf("Changing Mode...\n");
                    iprintf("Press A for Slow\n");
                    iprintf("Press B for Fast\n");
                    iprintf("Press nothing to cancel\n");
                    swiWaitForVBlank();
                    scanKeys();
                    keys = keysDown();
                    if(keys & KEY_A) { 
                        choice = 3;
                        break;
                    }
                    if(keys & KEY_B) { 
                        choice = 4;
                        break;
                    }
                }
                break;
        }
        selected = false; // reset selection after action
    }

    // Display normal menu when not selected
    if(choice == 3) {
        items[3].name = "Mode: Slow\n\n";
    } else if (choice == 4) {
        items[3].name = "Mode: Fast\n\n";
    }
    iprintf("%s", items[3].name); // Always show the Mode header
    for (int x = 0; x < itemCount; x++) {
        // Basically writes all the menu items to the screen
        char cursorChar = (x == cursor) ? '>' : ' ';
        iprintf("%c %s\n\n", cursorChar, items[x].name);
    }

    return choice;
}

int menuUpDown(int keys, int cursor) {
    if (keys & KEY_L) { // Changed to LEFT/RIGHT so that other keys can be used for gameplay. 
        cursor--;
        if (cursor < 0) {
            cursor = 2;
        }
    } else if (keys & KEY_R) {
        cursor++;
        if (cursor > 2) {
            cursor = 0;
        }
    }
    return cursor;
}