/*
 * Ov002_SetPanelBgLayers - set up BG1..BG3 of the main engine for the panel,
 * and optionally wipe what is on them.
 *
 * Each control word keeps only the bits the mask 0x43 covers - the two
 * priority bits and the mosaic bit - and replaces everything else. BG1 becomes
 * character base 1, screen base 0x1c, 512x256; BG3 becomes screen base 0x1e.
 * BG2 gets screen base 0x1f either way and the context's flag at +0x5c decides
 * bit 7, its palette mode: set means 256 colours, clear means sixteen.
 *
 * The three screen blocks are 0x800 each, and clearing them is what the caller
 * asks for when it is about to redraw rather than scroll.
 *
 * THUMB. The register address is held in a pointer and indexed rather than
 * cast three times: the ROM loads 0x0400000a from the pool once and reaches
 * BG2 and BG3 as [r1,#2] and [r1,#4].
 */

typedef unsigned short u16;

typedef struct {
    char pad0000[0x5c];
    int bBg2Is256Colour;            /* +0x5c */
} Ov002PanelCtx;

extern Ov002PanelCtx *data_ov002_0207f614;

extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(unsigned int nData, void *pDst, unsigned int nSize);

void func_ov002_020553ec(int bClear)
{
    Ov002PanelCtx *ctx;
    volatile u16 *pBgCnt;

    ctx = data_ov002_0207f614;
    pBgCnt = (volatile u16 *)0x0400000a;
    if (ctx->bBg2Is256Colour != 0) {
        pBgCnt[0] = (u16)(0x5c04 | (pBgCnt[0] & 0x43));
        pBgCnt[1] = (u16)(0x1f80 | (pBgCnt[1] & 0x43));
        pBgCnt[2] = (u16)(0x1e00 | (pBgCnt[2] & 0x43));
    } else {
        pBgCnt[0] = (u16)(0x5c04 | (pBgCnt[0] & 0x43));
        pBgCnt[1] = (u16)(0x1f00 | (pBgCnt[1] & 0x43));
        pBgCnt[2] = (u16)(0x1e00 | (pBgCnt[2] & 0x43));
    }

    if (bClear) {
        MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
        MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
        MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    }
}
