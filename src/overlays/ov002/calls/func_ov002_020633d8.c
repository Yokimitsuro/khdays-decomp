/*
 * Ov002_DrawNoticeGauge - draw the notice bar and its beads.
 *
 * Nothing happens until a notice is up. The bar is redrawn from the entry that
 * owns it, and outside the one language that hides them, a bead is stamped every
 * two units across: the filled cue up to the count that is reached, then the
 * empty cue for the rest of the row.
 *
 * ARM.
 */

typedef struct {
    char pad000[0x94];
    int nNotice;
    char pad098[0xa0];
    char statusCtx[0x3c];
    char pad174[0x4c];
    int nFilled;
    int nTotal;
} Ov002CaptionScene;

extern int data_ov002_0207f62c;

extern int func_020235d0(int nField, int nKind);
extern void func_020300f8(void *pCtx);
extern void func_0203034c(void *pCtx, int nScreenBase, int a, int b, int c);

extern int func_ov002_02053558(int nCue);
extern void func_ov002_020535a4(int nHandle);
extern int func_ov002_020535c4(int nHandle, short nPos, int nMode);
extern int func_ov002_02053bb8(int nId);
extern void func_ov002_02053cd4(int nId);

void func_ov002_020633d8(void)
{
    int i;
    int nCueFilled;
    int nCueEmpty;
    int nPos;
    Ov002CaptionScene *s;

    s = *(Ov002CaptionScene **)((char *)&data_ov002_0207f62c + 4);
    if (s->nNotice == 0) {
        return;
    }

    func_ov002_020535a4(func_ov002_02053558(0x41a));
    func_020300f8(s->statusCtx);
    func_0203034c(s->statusCtx, func_ov002_02053bb8(0x1a), 0x16, 0xf, 0xc);

    if (func_020235d0(0, 9) != 0x165) {
        nCueFilled = func_ov002_02053558(0x400);
        nCueEmpty = func_ov002_02053558(0x401);
        i = 0;
        if (i < s->nFilled) {
            nPos = 2;
            do {
                func_ov002_020535c4(nCueFilled, (short)nPos, 0x16);
                nPos += 2;
                i++;
            } while (i < s->nFilled);
        }
        if (i < s->nTotal) {
            nPos = i * 2 + 2;
            do {
                func_ov002_020535c4(nCueEmpty, (short)nPos, 0x16);
                nPos += 2;
                i++;
            } while (i < s->nTotal);
        }
    }
    func_ov002_02053cd4(0x1a);
}
