#include "menu.h"

// Menu items array
struct menuItem items[] = {
    {"Start Game", 0},
    {"Reset", 1},
    {"Mode", 2}
};

// Global menu variables
int keys;
int itemCount = 3;
int cursor = 0;
bool selected = false;

// Function to wait for milliseconds using VBlank
void waitMilliseconds(int ms) {
    int frames = (ms * 60) / 1000; // Convert ms to frames (60 FPS)
    for(int i = 0; i < frames; i++) {
        swiWaitForVBlank();
    }
}

void menuLogic() {
    for (int x = 0; x < itemCount; x++) {
        char cursorChar = (x == cursor) ? '>' : ' ';
        char starChar = (x == cursor && selected) ? '*' : ' ';
        
        iprintf("%c%c %s\n\n", cursorChar, starChar, items[x].name);
        if(selected) {
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
                    break;
                case 2:
                    // Show mode change message for 2 seconds or until B is pressed
                    for(int countdown = 120; countdown > 0; countdown--) { // 2 seconds at 60fps
                        consoleClear();
                        iprintf("Changing Mode...\n");
                        iprintf("Press X for 1 player\n");
                        iprintf("Press Y for 2 player\n");
                        iprintf("Press B to cancel\n");
                        swiWaitForVBlank();
                        scanKeys();
                        if(keysDown() & KEY_B) break;
                        if(keysDown() & KEY_X) { /* Set to 1 player mode */
                            // Implement 1 player mode logic here
                        }
                        if(keysDown() & KEY_Y) { /* Set to 2 player mode */
                            // Implement 2 player mode logic here
                        }
                    }
                    break;
            }
            selected = false; // reset selection after action
        }
    }
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