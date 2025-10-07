#ifndef SPRITES_H
#define SPRITES_H

#include <nds.h>

// External framebuffer pointer
extern u16 *fb;

// Color constants array indices
enum ColorIndex {
    COLOR_BLACK = 0,
    COLOR_WHITE = 1,
    COLOR_RED = 2
};

// Color array
extern const u16 colors[3];

// Rectangle structure
typedef struct {
    int x, y, w, h;
} Rect;

// Ball structure
typedef struct {
    int x, y, r;
    int vx, vy;
} Ball;

// Function declarations
void putPixel(int x, int y, u16 color);
void fillRect(int x, int y, int w, int h, u16 color);
void fillCircle(int cx, int cy, int r, u16 color);
void initDS();

#endif // SPRITES_H