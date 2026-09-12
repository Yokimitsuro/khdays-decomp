/* func_ov011_0205c6fc -- Ov011_ApplyPaneFade: drive one title pane's fade through its
 * blend hooks.
 *
 * Copies the overlay's fade hook table (two entries per pane) to the stack, picks the
 * pane's pair, and derives the blend flags from the scene mode.  Once the cursor has
 * reached the pane's fade end the pane is finished: state 1 (fade in) blends at delta 0
 * and fires the done hook, state 2 (fade out) blends at -16 and clears its auxiliary
 * byte.  While the fade is still running the alpha is interpolated over the fade window
 * (0..16) and the pane's signed delta is set to alpha-16 (fade in) or -alpha (fade out)
 * before the blend hook is called with it.
 *
 * Levers: the hook table copy and the pair pointer are computed before the pane offset,
 * so the pane index is only copied out of r0 for the block copy (ip); the fade end is
 * read as a u32; declaration order nOffset, pScene, pHooks, hooks, pPane; the timeout
 * blend passes an explicit 0 that shares the zero stored into the delta byte.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;

#define FADE_ALPHA_MAX 0x10
#define FLAGS_MODE_BIT 0x10
#define FLAGS_BASE     0xc

typedef struct Ov011FadeHookTable {
    void (*apfn[4])();       /* pane 0: blend, done; pane 1: blend, done */
} Ov011FadeHookTable;

/* khdays: shared-bss */
int data_ov011_0205e960 = 0;             /* gOv011Cursor */
u8 *data_ov011_0205e964 = 0;             /* gpOv011Scene */
extern Ov011FadeHookTable data_ov011_0205dc90;
extern long long func_0202060c(int nNum, int nDen);

void func_ov011_0205c6fc(int nPane)
{
    int nOffset;
    u8 *pScene;
    void (**pHooks)();
    Ov011FadeHookTable hooks;
    u8 *pPane;
    int nFlags;
    u32 nEnd;
    u16 nStart;
    int nAlpha;
    int nDelta;
    u32 nCursor;

    hooks = data_ov011_0205dc90;
    pHooks = &hooks.apfn[nPane * 2];
    nOffset = nPane * 0x10940;
    pScene = data_ov011_0205e964;
    pPane = pScene + 0x14 + nOffset;
    nFlags = (*(int *)(pScene + 4) >= 2 ? FLAGS_MODE_BIT : 0) | FLAGS_BASE;
    nEnd = *(u16 *)(pPane + 0x1092a);
    nCursor = data_ov011_0205e960;

    if (nCursor >= nEnd) {
        switch (*(u8 *)(pPane + 0x10931)) {
        case 1:
            *(s8 *)(pPane + 0x10930) = 0;
            pHooks[0](nFlags, 0);
            pHooks[1]();
            break;
        case 2:
            *(s8 *)(pPane + 0x10930) = 0;
            *(s8 *)(pPane + 0x10933) = 0;
            pHooks[0](nFlags, -FADE_ALPHA_MAX);
            break;
        }
    } else {
        int nState;

        if (nEnd <= nCursor) {
            nAlpha = FADE_ALPHA_MAX;
        } else {
            nStart = *(u16 *)(pPane + 0x10928);
            nAlpha = (u16)func_0202060c((int)(nCursor - nStart) * FADE_ALPHA_MAX, nEnd - nStart);
        }
        nState = *(u8 *)(pScene + nOffset + 0x10945);
        nDelta = (short)nAlpha;
        switch (nState) {
        case 1:
            *(s8 *)(pPane + 0x10930) = (s8)(nDelta - FADE_ALPHA_MAX);
            pHooks[0](nFlags, *(s8 *)(pPane + 0x10930));
            break;
        case 2:
            *(s8 *)(pPane + 0x10930) = (s8)(-nDelta);
            pHooks[0](nFlags, *(s8 *)(pPane + 0x10930));
            break;
        }
    }
}
