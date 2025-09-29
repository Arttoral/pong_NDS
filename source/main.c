#include <nds.h>
#include <stdio.h>


int main(void) {

    videoSetMode(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_SPRITE);
    oamInit(&oamMain, SpriteMapping_Bmp_1D_128, false);

    videoSetModeSub(MODE_0_2D);
    vramSetBankD(VRAM_D_SUB_SPRITE);
    oamInit(&oamSub, SpriteMapping_Bmp_1D_128, false);


while (1) {
    scanKeys();
    
    swiWaitForVBlank();
    oamUpdate(&oamSub);
    oamUpdate(&oamMain);

    }
}
