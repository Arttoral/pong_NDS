#include "sprites.h"

// Global framebuffer pointer
u16 *fb;

// Color array
const u16 colors[3] = {
    RGB15(0,0,0)   | BIT(15),  // BLACK
    RGB15(31,31,31)| BIT(15),  // WHITE
    RGB15(31,0,0)  | BIT(15)   // RED
};

// Initialize graphics and framebuffer
void initDS() {
    videoSetMode(MODE_FB0);
    vramSetBankA(VRAM_A_LCD);
    fb = (u16*)VRAM_A;
    // Initialize sub screen for console text
    videoSetModeSub(MODE_0_2D);
    vramSetBankC(VRAM_C_SUB_BG); // Use VRAM_C for sub screen backgrounds
  
}

// Draw pixel to the screen
void putPixel(int x, int y, u16 color) {
    if ((unsigned)x < SCREEN_WIDTH && (unsigned)y < SCREEN_HEIGHT) {
        fb[y * SCREEN_WIDTH + x] = color;
    }
}

// Draw rectangle on screen given position, width, height, color
void fillRect(int x, int y, int w, int h, u16 color) {
    if (w <= 0 || h <= 0) return;

    int x2 = x + w;
    int y2 = y + h;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x2 > SCREEN_WIDTH)  x2 = SCREEN_WIDTH;
    if (y2 > SCREEN_HEIGHT) y2 = SCREEN_HEIGHT;

    for (int j = y; j < y2; ++j) {
        u16 *row = &fb[j * SCREEN_WIDTH + x];
        for (int i = x; i < x2; ++i) *row++ = color;
    }
}

// Draw circle on screen given position, radius, color
void fillCircle(int cx, int cy, int r, u16 color) {
    if (r <= 0) return;
    int x = r, y = 0, err = 1 - r;
    while (x >= y) {
        for (int i = cx - x; i <= cx + x; ++i) {
            putPixel(i, cy + y, color);
            putPixel(i, cy - y, color);
        }
        for (int i = cx - y; i <= cx + y; ++i) {
            putPixel(i, cy + x, color);
            putPixel(i, cy - x, color);
        }
        y++;
        if (err < 0) err += 2*y + 1;
        else { x--; err += 2*(y - x) + 1; }
    }
}