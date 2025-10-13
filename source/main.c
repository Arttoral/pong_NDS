#include <nds.h>
#include <stdio.h>
#include "menu.h"
#include "sprites.h"
#include <maxmod9.h>

#include "soundbank.h"
#include "soundbank_bin.h"


// Declare console object for sub screen
PrintConsole consoleSub;

void basicGame(Rect *left, Rect *right, Ball *ball, int paddleSpeed, int keys, int held);

int main(void) {
    // Initialize graphics
    initDS();
    mmInitDefaultMem((mm_addr)soundbank_bin);
    mmLoad( MOD_PONGSONGTHEMETEST );
    mmStart( MOD_PONGSONGTHEMETEST, MM_PLAY_LOOP );

    // Initialize console on sub screen
    consoleInit(&consoleSub, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    consoleSelect(&consoleSub); // Make this console active for iprintf

    //establish paddles and ball
    Rect left  =  { 8,  (SCREEN_HEIGHT/2) - 24, 8, 48 };
    Rect right =  { SCREEN_WIDTH - 16, (SCREEN_HEIGHT/2) - 24, 8, 48 };
    Ball ball  =  { SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 5, 2, 2 };

    //paddle speed
    const int paddleSpeed = 3;

    /* TODO: Add background graphics
    // Setting up the top screen
    videoSetMode(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_BG);

    int topBg = bgInit(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

    dmaCopy(topTiles, bgGetGfxPtr(topBg), topTilesLen);
    dmaCopy(topMap, bgGetMapPtr(topBg), topMapLen);
    dmaCopy(topPal, BG_PALETTE, topPalLen);

    // Setting up the bottom screen
    videoSetModeSub(MODE_0_2D);
    vramSetBankC(VRAM_C_SUB_BG);

    int bottomBg = bgInitSub(3, BgType_Text8bpp, BgSize_T_256x256, 2, 3); //need to set the indices to different numbers so they don't overwrite

    dmaCopy(bottomTiles, bgGetGfxPtr(bottomBg), bottomTilesLen);
    dmaCopy(bottomMap, bgGetMapPtr(bottomBg), bottomMapLen);
    dmaCopy(bottomPal, BG_PALETTE_SUB, bottomPalLen);
    */

    
    while (1) {
        swiWaitForVBlank();
        scanKeys();
        int held = keysHeld();
        keys = keysDown();

        // Handle input first
        if (keys & KEY_A) { // A Key Selects current menu item (only if not already selected)
            selected = true;
        } else if (!selected) { // handle movement only when not selected
            cursor = menuUpDown(keys, cursor);
        }
        // Clear console before menu display
        consoleClear();
        
        // Reset cursor to ensure proper positioning
        printf("\x1b[0;0H");
        
        // Add buffer line to prevent cutoff
        iprintf("\n");
        
        // Menu logic
        int mode = menuLogic();
        switch (mode) {
            case 1://start game
                while(1) {
                    consoleClear();
                    iprintf("Game Start!\n");
                    iprintf("Press B to cancel\n");
                    swiWaitForVBlank();
                    scanKeys();
                    basicGame(&left, &right, &ball, paddleSpeed, keys, held);
                    if(keysDown() & KEY_B) break;
                }
                break;
            case 2://reset
                 // 2 seconds at 60fps
                    consoleClear();
                    iprintf("Resetting...\n");
                    iprintf("Press A to cancel\n");
                    swiWaitForVBlank();
                    ball.x = SCREEN_WIDTH/2;
                    ball.y = SCREEN_HEIGHT/2;
                    ball.vx = 2;
                    ball.vy = 2;
                    left.y = (SCREEN_HEIGHT/2) - 24;
                    right.y = (SCREEN_HEIGHT/2) - 24;
                    basicGame(&left, &right, &ball, paddleSpeed, keys, held);
                for(int countdown = 120; countdown > 0; countdown--) {
                    swiWaitForVBlank();
                }
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
    return 0;
}


void basicGame(Rect *left, Rect *right, Ball *ball, int paddleSpeed, int keys, int held) {
        keys = keysDown();
        held = keysHeld();
        //move paddle based on key pressed: up down moves left and W S moves right paddle
        if (held & KEY_UP)    left->y  -= paddleSpeed;
        if (held & KEY_DOWN)  left->y  += paddleSpeed;
        if (held & KEY_X)     right->y -= paddleSpeed;
        if (held & KEY_B)     right->y += paddleSpeed;

        //ball moves
        ball->x += ball->vx;
        ball->y += ball->vy;

        if (ball->y - ball->r < 0) { ball->y = ball->r; ball->vy = -ball->vy; }
        if (ball->y + ball->r >= SCREEN_HEIGHT) { ball->y = SCREEN_HEIGHT - 1 - ball->r; ball->vy = -ball->vy; }

        if (ball->x - ball->r <= left->x + left->w &&
            ball->y >= left->y && ball->y <= left->y + left->h &&
            ball->vx < 0) {
            ball->x = left->x + left->w + ball->r;
            ball->vx = -ball->vx;
        }
        // Right paddle
        if (ball->x + ball->r >= right->x &&
            ball->y >= right->y && ball->y <= right->y + right->h &&
            ball->vx > 0) {
            ball->x = right->x - ball->r;
            ball->vx = -ball->vx;
        }

        // If ball goes past a paddle, reset to center
        if (ball->x < -ball->r || ball->x > SCREEN_WIDTH + ball->r) {
            ball->x = SCREEN_WIDTH/2;
            ball->y = SCREEN_HEIGHT/2;
             ball->vx = (ball->vx < 0) ? 2 : -2; // flip serve
            ball->vy = 2;
        }

        dmaFillHalfWords(colors[COLOR_BLACK], fb, SCREEN_WIDTH * SCREEN_HEIGHT * 2);

        fillRect(left->x,  left->y,  left->w,  left->h,  colors[COLOR_WHITE]);
        fillRect(right->x, right->y, right->w, right->h, colors[COLOR_WHITE]);

        fillCircle(ball->x, ball->y, ball->r, colors[COLOR_RED]);
}