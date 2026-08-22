/*
 * Ov002_RunScrollHooks - hand the frame's scroll values to whoever wants them.
 *
 * Skipped while the context is held, and again when nothing has asked for an
 * update. Three hooks then run in turn, each only if it is installed. The first
 * has a default: with no hook, the sub engine's BG0 scroll is written straight,
 * the vertical half taking the value and the horizontal half zero. The other
 * two get a pair of values each and a fixed 0xc0. The request flag is cleared
 * on the way out.
 *
 * ARM.
 */

typedef volatile unsigned int vu32;

extern int data_ov002_0207f614;

void func_ov002_02054d80(void)
{
    unsigned char *pCtx;
    void (*pfnScroll)(int nA, int nB);
    void (*pfnHook)(int nA, int nB, int nC, int nD);

    pCtx = *(unsigned char **)&data_ov002_0207f614;
    if (*(int *)(pCtx + 0x1b0) != 0) {
        return;
    }
    if (*(int *)(pCtx + 0x2a8) == 0) {
        return;
    }

    pfnScroll = *(void (**)(int, int))(pCtx + 0x230);
    if (pfnScroll == 0) {
        *(vu32 *)0x04001010 = 0x01ff0000 & *(int *)(pCtx + 0x2b0) << 16;
    } else {
        pfnScroll(*(int *)(pCtx + 0x2ac), *(int *)(pCtx + 0x2b0));
    }

    pfnHook = *(void (**)(int, int, int, int))(pCtx + 0x238);
    if (pfnHook != 0) {
        pfnHook(0, *(int *)(pCtx + 0x2b4), *(int *)(pCtx + 0x2b8), 0xc0);
    }

    pfnHook = *(void (**)(int, int, int, int))(pCtx + 0x23c);
    if (pfnHook != 0) {
        pfnHook(*(int *)(pCtx + 0x2bc), *(int *)(pCtx + 0x2c0), 0, 0xc0);
    }

    *(int *)(pCtx + 0x2a8) = 0;
}
