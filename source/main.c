#include <nds.h>
#include <stdio.h>

static u16 *fb;


// draw pixel to the screen
static inline void putPixel(int x, int y, u16 color) {
    if ((unsigned)x < SCREEN_WIDTH && (unsigned)y < SCREEN_HEIGHT) {
        fb[y * SCREEN_WIDTH + x] = color;
    }
}

//draw rectange on screen given position, width, height, color
static void fillRect(int x, int y, int w, int h, u16 color) {
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

//draw circle on screen given position, radius, color
static void fillCircle(int cx, int cy, int r, u16 color) {
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


//structs for rectangle and circle
typedef struct {
    int x, y, w, h;
} Rect;

typedef struct {
    int x, y, r;
    int vx, vy;
} Ball;


int main(void) {
    videoSetMode(MODE_FB0);
    vramSetBankA(VRAM_A_LCD);
    fb = (u16*)VRAM_A;

    //colors
    const u16 BLACK = RGB15(0,0,0)   | BIT(15);
    const u16 WHITE = RGB15(31,31,31)| BIT(15);
    const u16 RED   = RGB15(31,0,0)  | BIT(15);

    //establish paddles and ball
    Rect left  =  { 8,  (SCREEN_HEIGHT/2) - 24, 8, 48 };
    Rect right =  { SCREEN_WIDTH - 16, (SCREEN_HEIGHT/2) - 24, 8, 48 };
    Ball ball  =  { SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 5, 2, 2 };

    //paddle speed
    const int paddleSpeed = 3;

    
    while (1) {
        swiWaitForVBlank();
        scanKeys();
        int held = keysHeld();

        //move paddle based on key pressed: up down moves left and W S moves right paddle
        if (held & KEY_UP)    left.y  -= paddleSpeed;
        if (held & KEY_DOWN)  left.y  += paddleSpeed;
        if (held & KEY_X)     right.y -= paddleSpeed;
        if (held & KEY_B)     right.y += paddleSpeed;

        //ball moves
        ball.x += ball.vx;
        ball.y += ball.vy;

        if (ball.y - ball.r < 0) { ball.y = ball.r; ball.vy = -ball.vy; }
        if (ball.y + ball.r >= SCREEN_HEIGHT) { ball.y = SCREEN_HEIGHT - 1 - ball.r; ball.vy = -ball.vy; }

        if (ball.x - ball.r <= left.x + left.w &&
            ball.y >= left.y && ball.y <= left.y + left.h &&
            ball.vx < 0) {
            ball.x = left.x + left.w + ball.r;
            ball.vx = -ball.vx;
        }
        // Right paddle
        if (ball.x + ball.r >= right.x &&
            ball.y >= right.y && ball.y <= right.y + right.h &&
            ball.vx > 0) {
            ball.x = right.x - ball.r;
            ball.vx = -ball.vx;
        }

        // If ball goes past a paddle, reset to center
        if (ball.x < -ball.r || ball.x > SCREEN_WIDTH + ball.r) {
            ball.x = SCREEN_WIDTH/2;
            ball.y = SCREEN_HEIGHT/2;
             ball.vx = (ball.vx < 0) ? 2 : -2; // flip serve
            ball.vy = 2;
        }


        dmaFillHalfWords(BLACK, fb, SCREEN_WIDTH * SCREEN_HEIGHT * 2);

        fillRect(left.x,  left.y,  left.w,  left.h,  WHITE);
        fillRect(right.x, right.y, right.w, right.h, WHITE);

        fillCircle(ball.x, ball.y, ball.r, RED);
    }
    return 0;
}
