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
        
        // Handle input first
        if (keys & KEY_A) { // A Key Selects current menu item (only if not already selected)
            selected = true;
        } else if (!selected) { // handle movement only when not selected
            cursor = menuUpDown(keys, cursor);
        }
        
        // Menu logic
        int mode = menuLogic();
        switch (mode) {
            case 1://start game
                // Add start game logic here
                break;
            case 2://reset
                // Add reset logic here
                break;
            case 3://1 player mode

                break;
            case 4://2 player mode
                iprintf("\n\n2 Player Mode");
                break;
            default:
                break;  
        }
    }
}
