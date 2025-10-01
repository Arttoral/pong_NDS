#include <nds.h>
#include <stdio.h>
#include "menu.h"

// Declare console object for sub screen
PrintConsole consoleSub;

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
    
    while (1) {
        swiWaitForVBlank();
        consoleClear();
        scanKeys();
        keys = keysDown();
        
        // Menu logic
        menuLogic();
        


        
        // Handle input
        if (keys & KEY_A) { // A Key Selects current menu item
            selected = true;
        } else { // handle any other key besides A
            if (selected == false) { // we don't want to move the cursor if its not shown
                cursor = menuUpDown(keys, cursor);
            }
        }
    }
}
