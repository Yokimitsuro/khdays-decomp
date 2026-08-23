/*
 * Ov002_RequestPageRetry - go round again, now or as soon as it can.
 *
 * The sibling of the advance request: it only applies once the page is closing,
 * and it queues the retry step behind the same handover slot when the screen or
 * the caption is not ready for it yet.
 *
 * ARM.
 */

typedef struct {
    char pad000[4];
    int bClosing;
    char pad008[0x30];
    void (*pfnDone)(void);
} Ov002PageContext;

extern Ov002PageContext *data_ov002_0207f634;

extern int func_ov002_02052b44(void);
extern int func_ov002_02062e04(int nMode, int nTake);
extern void func_ov002_0206461c(void);
extern int func_ov002_0206b7a4(void);

void func_ov002_02064654(void)
{
    Ov002PageContext *ctx;

    ctx = data_ov002_0207f634;
    if (ctx->bClosing == 0) {
        return;
    }
    if (ctx->pfnDone != 0) {
        return;
    }
    if (func_ov002_0206b7a4() != 0) {
        return;
    }

    if (func_ov002_02052b44() != 0 && func_ov002_02062e04(1, 0) != 0) {
        func_ov002_0206461c();
    } else {
        ctx->pfnDone = func_ov002_0206461c;
    }
}
