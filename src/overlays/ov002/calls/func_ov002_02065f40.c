/*
 * Ov002_SetPageReady - say whether this page is ready and act on it.
 *
 * Nothing is recorded while the page is still busy, the machine is not idle or
 * the board still has work of its own. Otherwise the flag is kept for the slot
 * on screen, that slot also starts the fade, and a ready page asks the caption
 * screen for its line, playing the cue that goes with it once it is accepted.
 *
 * ARM.
 */

typedef struct {
    char pad000[4];
    int nSlot;
    char pad008[0x20];
    int bReady;
} Ov002TabCtx;

extern Ov002TabCtx *data_ov002_0207f99c;

extern int func_020208e0(void);
extern int func_02030788(void);
extern void func_02033b78(int a, int b);

extern int func_ov002_02053558(int nCue);
extern void func_ov002_020535a4(int nHandle);
extern int func_ov002_02062e04(int nMode, int nTake);
extern int func_ov002_02063888(void);
extern int func_ov002_0206b7a4(void);

void func_ov002_02065f40(int bReady)
{
    Ov002TabCtx *ctx;

    ctx = data_ov002_0207f99c;
    if (func_ov002_0206b7a4() != 0) {
        return;
    }
    if (func_020208e0() != 0) {
        return;
    }
    if (func_ov002_02063888() != 0) {
        return;
    }

    if (ctx->nSlot == func_02030788()) {
        ctx->bReady = bReady;
    }
    if (ctx->nSlot == func_02030788()) {
        func_02033b78(0, 1);
    }

    if (bReady != 0 && func_ov002_02062e04(0, 0) != 0) {
        func_ov002_020535a4(func_ov002_02053558(0x5e1));
    }
}
