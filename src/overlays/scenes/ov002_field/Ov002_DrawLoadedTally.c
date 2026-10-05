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

extern void GetResourceSubBlock_CHAR(int nId, void **ppOut);
extern void MIi_CpuCopyFast(const void *pSrc, void *pDst, unsigned int nSize);
extern int GameState_GetField(int a, int b);
extern void Text_DrawDirectional_2(void *pCtx, int a, int b, int c, int d, void *pText);

extern void Ov002_DestroyOwnedEntry(void *pNode, int nMode);
extern void *Ov002_VariadicMapForward(void *pMsg, int nKind, void *pOut, int nSize, ...);
extern int Ov002_GetPanelField0058(void);
extern void Ov002_DrawNoticeGauge(void);

void Ov002_DrawLoadedTally(void *pNode)
{
    void *pSub;
    char aText[0x40];
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    if (s == 0) {
        Ov002_DestroyOwnedEntry(pNode, 1);
        return;
    }

    GetResourceSubBlock_CHAR(*(int *)((char *)pNode + 8), &pSub);
    if (Ov002_GetPanelField0058() != 0) {
        MIi_CpuCopyFast(*(void **)((char *)pSub + 0x14),
                        *(void **)((char *)s->pTiles2 + 0x20),
                        *(unsigned int *)((char *)pSub + 0x10));
        if (GameState_GetField(0, 9) != 0x165 && s->bRange != 0) {
            Ov002_VariadicMapForward(s->msgCtx, 1, aText, 0x20, s->nTo - s->nFrom,
                                s->nTo);
            Text_DrawDirectional_2(s->lineCtx, 0x76, 2, 0xf, 0x21, aText);
        }
    }

    Ov002_DestroyOwnedEntry(pNode, 1);
    Ov002_DrawNoticeGauge();
}
