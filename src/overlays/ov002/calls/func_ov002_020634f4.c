/*
 * Ov002_RedrawCaptionTallies - redraw the two tally rows of the caption screen.
 *
 * Each row is only touched while it is up, and both are drawn from the same
 * entry: the upper one at column 4 of row 0xd, the lower one at column 0x14 of
 * row 2.
 *
 * ARM.
 */

typedef struct {
    char pad000[0x8c];
    int nTallyUp;
    int nTallyLow;
    char pad094[0x2c];
    char tallyCtx[0x3c];
    char noticeCtx[0x3c];
} Ov002CaptionScene;

extern int data_ov002_0207f62c;

extern void func_0203034c(void *pCtx, int nScreenBase, int nColumn, int nRow,
                          int nWidth);
extern int func_ov002_02053bb8(int nId);

void func_ov002_020634f4(void)
{
    Ov002CaptionScene *s;

    s = *(Ov002CaptionScene **)((char *)&data_ov002_0207f62c + 4);
    if (s->nTallyUp != 0) {
        func_0203034c(s->tallyCtx, func_ov002_02053bb8(0x1a), 4, 0xd, 0xc);
    }
    if (s->nTallyLow != 0) {
        func_0203034c(s->noticeCtx, func_ov002_02053bb8(0x1a), 0x14, 2, 0xc);
    }
}
