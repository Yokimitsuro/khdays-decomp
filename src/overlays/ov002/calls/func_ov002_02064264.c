/*
 * Ov002_UpdatePageStamp - set the stamp that says how the page ended.
 *
 * The stamp only appears once the mark has reached where the count puts it and
 * the row allowance still covers that count; a mark that has gone all the way
 * to the end gets the better of the two stamps. Anything short of that clears
 * the stamp and plays the plainer cue instead.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    char pad000[0x30];
    u16 aStamp[2];
} Ov002PageContext;

typedef struct {
    int nTotal;
    int nRows;
    int nCurrent;
} Ov002PageProgress;

extern Ov002PageContext *data_ov002_0207f634;

extern long long func_02020400(int nNumerator, int nDenominator);
extern void GFXi_EnqueueCommand(int nCmd, int nDest, int nSrc, int nSize);

extern int func_ov002_02053558(int nCue);
extern void func_ov002_020535a4(int nHandle);
extern int func_ov002_02063698(void);
extern int func_ov002_020636ac(void);

void func_ov002_02064264(void)
{
    int nCurrent;
    Ov002PageProgress *p;
    Ov002PageContext *ctx;
    int nMark;
    int nTotal;

    ctx = data_ov002_0207f634;
    p = (Ov002PageProgress *)func_ov002_02063698();
    nMark = *(int *)func_ov002_020636ac();
    nCurrent = p->nCurrent;
    nTotal = p->nTotal;

    if (nMark >= (int)func_02020400(nCurrent * 0xe0, nTotal) &&
        p->nRows >= nCurrent) {
        if (nMark >= (int)func_02020400(nTotal * 0xe0, nTotal)) {
            ctx->aStamp[0] = 0x163f;
            ctx->aStamp[1] = 0x51b;
        } else {
            ctx->aStamp[0] = 0x13ea;
            ctx->aStamp[1] = 0x1e2;
        }
        GFXi_EnqueueCommand(0x1f, 0x142, (int)ctx->aStamp, 4);
        func_ov002_020535a4(func_ov002_02053558(0x418));
    } else {
        func_ov002_020535a4(func_ov002_02053558(0x417));
    }
}
