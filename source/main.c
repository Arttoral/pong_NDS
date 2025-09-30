#include <nds.h>
#include <stdio.h>

// Declare console object for sub screen
PrintConsole consoleSub;

struct menuItem {
    const char* name;
    int count;
};

struct menuItem items[] = {
    {"Start Game", 0},
    {"Reset", 1},
    {"Mode", 2}
};

int menuUpDown(int keys, int cursor);

int main(void) {
    // Initialize sub screen for console text
    videoSetModeSub(MODE_0_2D);
    vramSetBankC(VRAM_C_SUB_BG); // Use VRAM_C for sub screen backgrounds
    
    // Initialize console on sub screen
    consoleInit(&consoleSub, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    consoleSelect(&consoleSub); // Make this console active for iprintf
    
    // Initialize main screen (optional, for sprites later)
    videoSetMode(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_BG);
    
    int keys;
    int itemCount = 3;
    int cursor = 0;
    bool selected = false;
    
    while (1) {
        swiWaitForVBlank();
        consoleClear();
        scanKeys();
        keys = keysDown();

        for (int x = 0; x < itemCount; x++) {
            char cursorChar = (x == cursor) ? '>' : ' ';
            char starChar = (x == cursor && selected) ? '*' : ' ';
            
            iprintf("%c%c %s\n\n", cursorChar, starChar, items[x].name);
        }


        if (keys & KEY_A) { // A Key Selects current menu item
            selected = true;
        } else { // handle any other key besides A
            if (selected == false) { // we don't want to move the cursor if its not shown
                cursor = menuUpDown(keys, cursor);
            }
        }
    }
}

int menuUpDown(int keys, int cursor) {
    if (keys & KEY_UP) { // Changed to UP/DOWN for better menu navigation
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
