/* Repaints the sub-panel's row list.
 *
 * Each of the two panel records turns its drawn-cell count into the column its
 * last cell falls on and the row that column belongs to; both are zero when the
 * record has nothing drawn. A row is 46 cells wide. The shared block is copied
 * over the panel's own, then the second record's cells are redrawn whenever its
 * row is at or past the first's, and the first record's tail row follows when
 * its own flag is set. The bulk call is asked for the first record's span, cut
 * back so the total never passes the row width, and bit 1 of the state flags is
 * raised so the scene tick pushes the result.
 *
 * The local declaration order below is load-bearing, not style: it is what puts
 * the context in r5, the record pointer in r6 and the column in r4. Reordering
 * the declarations changes the register allocation and breaks the match. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 wCount;                         /* +0x00 */
    u16 wDrawn;                         /* +0x02 */
    u8 pad0004[2];
    u16 wSpan;                          /* +0x06 */
    u8 pad0008[0x10];
    int bDrawTail;                      /* +0x18 */
} Ov002PanelRecord;

typedef struct {
    u8 pad0000[0x20];
    int nSharedBlock;                   /* +0x20 */
    int nSharedCopy;                    /* +0x24 */
    u8 bStateFlags;                     /* +0x28 */
    u8 pad0029[0x103];
    Ov002PanelRecord aRecords[2];       /* +0x12c, stride 0x1c */
} Ov002SceneCtx;

extern Ov002SceneCtx *data_ov002_0207f618;

extern void MIi_CpuCopyFast(void *pSrc, void *pDst, int nSize);
extern void func_ov002_02057888(int nHandle, int nCell, int nMode);
extern void func_ov002_02057bb4(int nHandle, int nCell, int nCount, int nA, int nB,
                                int nC, int nD);

void func_ov002_020589b8(void) {
    Ov002SceneCtx *ctx = data_ov002_0207f618;
    Ov002PanelRecord *pRecA = &ctx->aRecords[0];
    int nRowB;
    Ov002PanelRecord *pRecB = &ctx->aRecords[1];
    int nRowA;
    int nColB;
    int nColA;
    int nLast;
    int i;
    int nCount;

    if (pRecA->wDrawn != 0) {
        nLast = pRecA->wDrawn - 1;
        nColA = nLast % 46 + 1;
        nRowA = nLast / 46;
    } else {
        nColA = 0;
        nRowA = nColA;
    }
    if (pRecB->wDrawn != 0) {
        nLast = pRecB->wDrawn - 1;
        nColB = nLast % 46 + 1;
        nRowB = nLast / 46;
    } else {
        nColB = 0;
        nRowB = nColB;
    }

    MIi_CpuCopyFast((void *)ctx->nSharedCopy, (void *)ctx->nSharedBlock, 0xc0);

    if (nRowB == nRowA) {
        for (i = 0; i < nColB; i++) {
            func_ov002_02057888(ctx->nSharedBlock, i, 0);
        }
    } else {
        i = 0;
        if (nRowA <= nRowB) {
            for (; i < nColB; i++) {
                func_ov002_02057888(ctx->nSharedBlock, i, 0);
            }
        }
    }

    if (pRecA->bDrawTail != 0) {
        for (; i < nColA; i++) {
            func_ov002_02057888(ctx->nSharedBlock, i, 1);
        }
    }

    nCount = pRecA->wSpan;
    if (nCount + pRecA->wDrawn > pRecA->wCount) {
        nCount = pRecA->wCount % 46 - nColA;
    }
    if (nCount + nColA > 46) {
        nCount = 46 - nColA;
    }
    func_ov002_02057bb4(ctx->nSharedBlock, i, nCount, 4, 0x2e, 0, 2);
    ctx->bStateFlags = ctx->bStateFlags | 2;
}
