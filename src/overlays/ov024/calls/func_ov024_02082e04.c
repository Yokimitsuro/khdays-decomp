/* MobiClip: arm the screen fade that the stepper then walks.
 *
 * Records which screens the fade covers and the direction, rewinds the step
 * counter to -1 so the stepper's first tick lands on 0, and hands each stream
 * that is still open over to the fade-out path.
 */
typedef unsigned char u8;

struct MobiClipPlayer {
    char pad0000[0x8bd8];
    int bStream0Present;
    int bStream1Present;
    char pad8be0[2];
    u8 nScreens;
    u8 pad8be3;
    int nToWhite;
    int nStep;
};

extern int data_ov024_02093a20;
extern void func_ov024_02084df4(int nStream);

void func_ov024_02082e04(int nScreens, int nToWhite)
{
    struct MobiClipPlayer *player =
        ((struct MobiClipPlayer **)&data_ov024_02093a20)[1];

    player->nToWhite = nToWhite;
    player->nStep = -1;
    player->nScreens = (u8)nScreens;

    switch (nScreens) {
    case 0:
        if (player->bStream0Present == 1) {
            player->bStream0Present = 2;
            func_ov024_02084df4(1);
        }
        break;
    case 1:
        player->bStream1Present = 2;
        func_ov024_02084df4(0);
        break;
    case 2:
        if (player->bStream0Present == 1) {
            player->bStream0Present = 2;
            func_ov024_02084df4(1);
        }
        if (player->bStream1Present == 1) {
            player->bStream1Present = 2;
            func_ov024_02084df4(0);
        }
        break;
    }
}
