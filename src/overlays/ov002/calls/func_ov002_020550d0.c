/*
 * Ov002_LoadPanelSlots - fill the panel's four slots from the icon archive.
 *
 * One archive file carries two sprite sets. Each slot names an id and an icon;
 * icons below thirteen come from the first set and the rest from the second,
 * thirteen apart. The blit table says per slot where the rows land in the
 * destination character data, how wide a row is and how many rows there are,
 * and slot 0 reads its rows from 0x120 into the icon while the others read
 * from 0x1e0. Colour fifteen of the icon's palette is overwritten from the
 * per-id colour table before the palette is copied out, and the help page for
 * the slot is printed.
 *
 * A slot with either half set to -1 is skipped, so the returned count and the
 * loaded mask only cover slots that really arrived; anSlotForId is reset to -1
 * first and then records where each id ended up. Afterwards the two help
 * palettes of each slot are loaded, but only the ones the context is not
 * already holding, and the archive file is freed on the way out.
 *
 * THUMB.
 *
 * The last two parameters are never read: both are written before any use, so
 * callers may pass anything. They are here because the ROM's frame reserves
 * the r2 and r3 parameter homes at +0x0c and +0x10 and keeps nPalDst and i
 * there - as plain locals they land in the spill run higher up and five slots
 * come out permuted. The frame is the evidence that the original declared
 * them.
 *
 * Three more shapes the frame depends on. The row offset is accumulated INSIDE
 * both arms of the `i == 0` test: written after the join, mwcc computes the
 * sum straight into r0, while from inside the arms it stays in nSrc's own
 * register and is copied out, which is what the ROM does. The reset loop
 * counts with j, not i. And the help-page cursor is `&pSlots[i]` off the
 * untouched parameter, with a separate pSlot walking the slots, so it becomes
 * an induction variable and sits below the help-palette walker.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    void *pScreen;
    void *pChar;
    void *pPalette;
} SpriteResSet;

typedef struct {
    int nDstOffset;
    int nRowBytes;
    unsigned int nRows;
} Ov002PanelBlit;

typedef struct {
    int nId;
    int nIcon;
    int aRest[2];
} Ov002PanelSlot;

typedef struct {
    int nFlipGate;              /* +0x000 */
    u8 pad0004[0x198];
    int nArchiveGroup;          /* +0x19c */
    u8 pad01a0[0xe];
    u8 bLoadedMask;             /* +0x1ae */
    u8 nLoadedCount;            /* +0x1af */
    u8 pad01b0[0x2c];
    void *ahHelpPltA[4];        /* +0x1dc */
    void *ahHelpPltB[4];        /* +0x1ec */
    int aHelpPltA[4];           /* +0x1fc */
    int aHelpPltB[4];           /* +0x20c */
    u8 pad021c[4];
    int anSlotForId[4];         /* +0x220 */
} Ov002PanelCtx;

extern void *func_0201ef9c(unsigned int nHandle, int nHeap);
extern void func_02024c94(SpriteResSet *pSet, void *pArc, int a, int b, int c);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern void func_ov002_02055068(int nPage, int *pCursor);
extern void func_02011a20(void *hRes, void *pOut);
extern void func_ov002_02063114(int a, int b);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

extern Ov002PanelCtx *data_ov002_0207f614;
extern Ov002PanelBlit data_ov002_0207dc90[];
extern u16 data_ov002_0207db8c[];
extern int data_ov002_0207dba8[];
extern int data_ov002_0207dbb8[];

int func_ov002_020550d0(Ov002PanelSlot *pSlots, SpriteResSet *pDst,
                        int nPalDst, int i)
{
    Ov002PanelCtx *ctx;
    int j;
    unsigned int k;
    int nCount;
    void *pArc;
    Ov002PanelSlot *pSlot;
    Ov002PanelBlit *pBlit;
    int nIcon;
    int nSrc;
    int nDst;
    int nPltBase;
    int nPltIcon;
    u16 *pIconPlt;
    SpriteResSet sLow;
    SpriteResSet sHigh;

    ctx = data_ov002_0207f614;
    nCount = 0;
    ctx->bLoadedMask = 0;
    pArc = func_0201ef9c(
        0x80000001 | ((ctx->nArchiveGroup + 0x8000) & 0xfffffc) << 7, 0xe);
    func_02024c94(&sLow, pArc, 0, 0, 0);
    func_02024c94(&sHigh, pArc, 0, 1, 1);

    for (j = 0; j < 4; j++) {
        ctx->anSlotForId[j] = -1;
    }

    i = 0;
    pSlot = pSlots;
    nPalDst = 0x40;
    pBlit = data_ov002_0207dc90;
    do {
        if (pSlot->nId != -1 && pSlot->nIcon != -1) {
            ctx->anSlotForId[pSlot->nId] = i;
            for (k = 0; k < pBlit->nRows; k++) {
                nDst = pBlit->nDstOffset + k * 0x400;
                nIcon = pSlot->nIcon;
                if (nIcon >= 0xd) {
                    nSrc = *(int *)((char *)sHigh.pChar + 0x14);
                    nIcon -= 0xd;
                } else {
                    nSrc = *(int *)((char *)sLow.pChar + 0x14);
                }
                if (i == 0) {
                    nSrc += k * 0x120 + 0x120 + nIcon * 0x6c0;
                } else {
                    nSrc += k * 0x120 + nIcon * 0x6c0 + 0x1e0;
                }
                MI_CpuCopy8(
                    (void *)nSrc,
                    (void *)(*(int *)((char *)pDst->pChar + 0x14) + nDst),
                    pBlit->nRowBytes);
            }

            nPltIcon = pSlot->nIcon;
            if (nPltIcon >= 0xd) {
                nPltBase = *(int *)((char *)sHigh.pPalette + 0xc);
                nPltIcon -= 0xd;
            } else {
                nPltBase = *(int *)((char *)sLow.pPalette + 0xc);
            }
            pIconPlt = (u16 *)(nPltBase + (nPltIcon * 0x20 + 0x20));
            pIconPlt[15] = data_ov002_0207db8c[pSlot->nId];
            MI_CpuCopy8(pIconPlt,
                        (void *)(*(int *)((char *)pDst->pPalette + 0xc)
                                 + nPalDst),
                        0x20);
            func_ov002_02055068(i, (int *)&pSlots[i]);
            nCount++;
            ctx->bLoadedMask = (u8)(ctx->bLoadedMask | 1 << pSlot->nId);
        }
        pBlit++;
        pSlot++;
        nPalDst += 0x20;
        i++;
    } while (i < 4);

    ctx->nLoadedCount = (u8)nCount;

    for (j = 0; j < 4; j++) {
        if (ctx->ahHelpPltA[j] == 0) {
            ctx->ahHelpPltA[j] = func_0201ef9c(
                ((ctx->nArchiveGroup + 0x8000) & 0xfffffc) << 7 | 0x80000000
                | (data_ov002_0207dba8[j] & 0x1ff), 0xe);
            func_02011a20(ctx->ahHelpPltA[j], &ctx->aHelpPltA[j]);
        }
        if (ctx->ahHelpPltB[j] == 0) {
            ctx->ahHelpPltB[j] = func_0201ef9c(
                ((ctx->nArchiveGroup + 0x8000) & 0xfffffc) << 7 | 0x80000000
                | (data_ov002_0207dbb8[j] & 0x1ff), 0xe);
            func_02011a20(ctx->ahHelpPltB[j], &ctx->aHelpPltB[j]);
        }
    }

    if (ctx->nFlipGate != 0) {
        func_ov002_02063114(1, 1);
    }
    if (pArc != 0) {
        NNSi_FndFreeFromDefaultHeap(pArc);
    }
    return nCount;
}
