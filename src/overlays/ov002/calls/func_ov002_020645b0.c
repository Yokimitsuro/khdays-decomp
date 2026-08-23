/*
 * Ov002_RequestPageAdvance - move the page on, now or as soon as it can.
 *
 * Nothing happens while a handover is already queued or the page still has work
 * of its own. Otherwise the fade is started and the advance is taken straight
 * away if the screen is free and the caption accepts it; when it is not, the
 * same step is left queued for the close step to make later.
 *
 * ARM.
 */

typedef struct {
    char pad000[0x38];
    void (*pfnDone)(void);
} Ov002PageContext;

extern Ov002PageContext *data_ov002_0207f634;

extern void func_02033b78(int a, int b);

extern int func_ov002_02052b44(void);
extern int func_ov002_02062e04(int nMode, int nTake);
extern void func_ov002_02064588(void);
extern int func_ov002_0206b7a4(void);

void func_ov002_020645b0(void)
{
    Ov002PageContext *ctx;

    ctx = data_ov002_0207f634;
    if (ctx->pfnDone != 0) {
        return;
    }
    if (func_ov002_0206b7a4() != 0) {
        return;
    }

    func_02033b78(0, 1);
    if (func_ov002_02052b44() != 0 && func_ov002_02062e04(1, 0) != 0) {
        func_ov002_02064588();
    } else {
        ctx->pfnDone = func_ov002_02064588;
    }
}
