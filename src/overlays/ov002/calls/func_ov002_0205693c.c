/*
 * Ov002_StepPanelScreen - run one frame of the mission panel.
 *
 * The state table is copied onto the stack and indexed by the panel state, so
 * every state is one call away; the hold flag is what stops the state machine
 * without stopping the rest of the frame. The countdown byte at +0x1ac ticks
 * down here and raises the flag at +0x1a8 on the frame it reaches zero.
 *
 * With either of the two mode bits set, and only outside the 256-colour case,
 * the slot icons are redrawn whenever the icon source hands back a set, and
 * the sub-screen items are placed from whatever the placer returns. The help
 * mode follows +0x50, the slot timers only tick while the panel is not held,
 * and the scroll is updated every frame regardless.
 *
 * The one-shot callback at +0x1d0 runs last and clears itself, and it is read
 * back off the global rather than the context pointer this function has been
 * using - the state it just ran may have replaced the context.
 *
 * ARM.
 */

typedef signed char s8;

typedef struct {
    void (*aSteps[12])(void);
} Ov002PanelStepTable;

typedef struct {
    char pad0000[0x50];
    int nHelpSource;                    /* +0x050 */
    char pad0054[8];
    int bBg2Is256Colour;                /* +0x05c */
    char pad0060[0x12c];
    int nPanelState;                    /* +0x18c */
    char pad0190[0x18];
    int nUnk01a8;                       /* +0x1a8 */
    unsigned char nCountdown;           /* +0x1ac */
    char pad01ad[3];
    int nHeld;                          /* +0x1b0 */
    char pad01b4[0x1c];
    void (*pOnceCallback)(void);        /* +0x1d0 */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;
extern Ov002PanelStepTable data_ov002_0207dc60;
extern unsigned char data_0204c240;

extern void func_ov002_02054e54(void);
extern void func_ov002_02055608(s8 *pIcons);
extern void func_ov002_020556dc(int nMode);
extern void func_ov002_02055730(s8 *pIndices);
extern void func_ov002_0205578c(void);
extern int func_ov002_0206ca50(s8 *pIcons);
extern s8 *func_ov002_0206cb4c(void);
extern int func_ov002_0206ccbc(void);

int func_ov002_0205693c(void)
{
    Ov002PanelContext *ctx;
    Ov002PanelStepTable sSteps;
    s8 aIcons[4];

    sSteps = data_ov002_0207dc60;
    ctx = data_ov002_0207f614;
    if (ctx->nHeld == 0) {
        sSteps.aSteps[ctx->nPanelState]();
    }
    if (ctx->nCountdown != 0) {
        ctx->nCountdown--;
        if (ctx->nCountdown == 0) {
            ctx->nUnk01a8 = 1;
        }
    }
    if (((data_0204c240 & 4) != 0 || (data_0204c240 & 8) != 0) &&
        ctx->bBg2Is256Colour == 0) {
        if (func_ov002_0206ca50(aIcons) != 0) {
            func_ov002_02055608(aIcons);
        }
        func_ov002_02055730(func_ov002_0206cb4c());
    }
    if (ctx->nHelpSource != 0) {
        func_ov002_020556dc(func_ov002_0206ccbc());
    }
    if (ctx->nHeld == 0) {
        func_ov002_0205578c();
    }
    func_ov002_02054e54();
    if (data_ov002_0207f614->pOnceCallback != 0) {
        data_ov002_0207f614->pOnceCallback();
        data_ov002_0207f614->pOnceCallback = 0;
    }
    return 0;
}
