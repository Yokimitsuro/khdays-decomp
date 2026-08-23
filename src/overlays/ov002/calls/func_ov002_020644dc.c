/*
 * Ov002_StepPageClose - close the page down and hand over when it is ready.
 *
 * The teardown runs once: the tag tracker for tag 9 is armed, the fade is
 * started, and the two closing passes are kicked - the first of them only when
 * the mode word says so.
 *
 * After that, the page's completion callback is made as soon as the screen is
 * free and the caption screen accepts the request that goes with it.
 *
 * ARM.
 */

typedef unsigned char u8;

typedef struct {
    char pad000[4];
    int bClosing;
    char pad008[0x30];
    void (*pfnDone)(void);
} Ov002PageContext;

extern Ov002PageContext *data_ov002_0207f634;
extern u8 data_0204c240;

extern void func_02033b24(int a, int b);

extern int func_ov002_02052b44(void);
extern int func_ov002_020536bc(int nTag);
extern void func_ov002_020536dc(int nEntry, int nValue);
extern int func_ov002_02062e04(int nMode, int nTake);
extern void func_ov002_02064328(void);
extern void func_ov002_02064358(void);
extern int func_ov002_0206629c(void);

int func_ov002_020644dc(void)
{
    Ov002PageContext *ctx;

    ctx = data_ov002_0207f634;
    if (ctx->bClosing == 0 && func_ov002_0206629c() != 0) {
        ctx->bClosing = 1;
        func_ov002_020536dc(func_ov002_020536bc(9), 1);
        func_02033b24(0, 0x2d);
    }

    if (data_0204c240 == 0 || (data_0204c240 & 1) != 0) {
        func_ov002_02064358();
    }
    func_ov002_02064328();

    if (ctx->pfnDone != 0 && func_ov002_02052b44() != 0 &&
        func_ov002_02062e04(1, 0) != 0) {
        ctx->pfnDone();
    }
    return 0;
}
