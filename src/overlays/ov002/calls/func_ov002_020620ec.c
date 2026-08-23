/*
 * Ov002_DrawLoadedTally - finish a tally load and draw the line that goes with
 * it.
 *
 * Without a live text context the load node is thrown away, and nothing is
 * drawn at all unless the wide layout is up. Otherwise the loaded block goes
 * straight into the context's second tile buffer.
 *
 * The line is only drawn when the current message is not the placeholder and
 * the context has a range to report: the message takes the span and its end as
 * its two arguments.
 *
 * THUMB.
 */

typedef struct {
    char pad000[0x138];
    char lineCtx[0x18];
    void *pTiles2;
    char pad154[0x60];
    char msgCtx[0x14];
    int nFrom;
    int nTo;
    int bRange;
} Ov002TextScene;

extern int data_ov002_0207f62c;

extern void func_02011988(int nId, void **ppOut);
extern void MIi_CpuCopyFast(const void *pSrc, void *pDst, unsigned int nSize);
extern int func_020235d0(int a, int b);
extern void func_020301c8(void *pCtx, int a, int b, int c, int d, void *pText);

extern void func_ov002_02052af4(void *pNode, int nMode);
extern void *func_ov002_0205287c(void *pMsg, int nKind, char *pOut, int nSize,
                                 ...);
extern int func_ov002_020575d0(void);
extern void func_ov002_020633d8(void);

void func_ov002_020620ec(void *pNode)
{
    void *pSub;
    char aText[0x40];
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    if (s == 0) {
        func_ov002_02052af4(pNode, 1);
        return;
    }

    func_02011988(*(int *)((char *)pNode + 8), &pSub);
    if (func_ov002_020575d0() != 0) {
        MIi_CpuCopyFast(*(void **)((char *)pSub + 0x14),
                        *(void **)((char *)s->pTiles2 + 0x20),
                        *(unsigned int *)((char *)pSub + 0x10));
        if (func_020235d0(0, 9) != 0x165 && s->bRange != 0) {
            func_ov002_0205287c(s->msgCtx, 1, aText, 0x20, s->nTo - s->nFrom,
                                s->nTo);
            func_020301c8(s->lineCtx, 0x76, 2, 0xf, 0x21, aText);
        }
    }

    func_ov002_02052af4(pNode, 1);
    func_ov002_020633d8();
}
