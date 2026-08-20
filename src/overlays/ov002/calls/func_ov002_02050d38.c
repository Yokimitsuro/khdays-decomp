/* Rebinds a sprite slot to cell nIndex of the resource it currently holds, then
 * releases that resource.
 *
 * The animation is stopped first when asked, the slot's low flag bits are
 * cleared, and the resource's cell and attribute sections are looked up. Size
 * and origin come from the cell, the pivot from the attribute section, and both
 * axes are narrowed to 15 bits unless the attribute's bit 0 says otherwise. The
 * slot is then reset to its default transform and marked fully visible, and the
 * resource handle is freed and cleared.
 *
 * Two shapes here are load-bearing rather than style. The section lookup is one
 * inlined helper called twice, once with nIndex and once with a literal 0: that
 * is what makes the second lookup compare unsigned against the folded index,
 * which no direct spelling of the test reproduces. And the two re-reads at +0x04
 * and +0x06 go through a signed short view, because the ROM reloads them with
 * ldrsh. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void func_0201f390(int bEnable);
extern void func_02025138(void *pRes);
extern int func_02017088(void *pRes);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);

static inline void *Ov002_GetSection(int nSec, int nCountOff, int nTableOff, u32 nIndex) {
    u32 nStride;
    int nTable;

    if (nSec != 0 && nIndex < *(u8 *)(nSec + nCountOff)) {
        nTable = nSec + *(u16 *)(nSec + nTableOff);
        nStride = *(u16 *)nTable;
        return (void *)(nTable + 4 + nStride * nIndex);
    }
    return 0;
}

void func_ov002_02050d38(u16 *p, int bFree, int nStop, u32 nIndex) {
    int nRes;
    u32 *pCell;
    u16 *pAttr;
    u32 nX;
    u32 nY;
    u32 nOrigin;

    if (nStop != 0) {
        func_0201f390(0);
        func_02025138(*(void **)(p + 0x16));
        func_0201f390(1);
    }

    *(u8 *)(p + 0x15) = (u8)(*(u8 *)(p + 0x15) & ~0xe0);

    nRes = func_02017088(*(void **)(p + 0x16));
    if (nRes != 0) {
        pCell = (u32 *)Ov002_GetSection(nRes + 0x3c, 1, 6, nIndex);
    } else {
        pCell = 0;
    }

    if (nRes != 0 && *(u16 *)(nRes + 0x34) != 0) {
        pAttr = (u16 *)Ov002_GetSection(nRes + *(u16 *)(nRes + 0x34), 1, 6, 0);
    } else {
        pAttr = 0;
    }

    nY = *(u32 *)(nRes + 0x2c) & 0xffff;
    nX = pAttr[0];
    if ((u8)((pCell[0] & 0x1c000000) >> 26) == 5) {
        nOrigin = *(u32 *)(nRes + 0x18) & 0xffff;
    } else {
        nOrigin = *(u32 *)(nRes + 8) & 0xffff;
    }
    if ((pAttr[1] & 1) == 0) {
        nX = (nX << 0xf) >> 0x10;
        nY = (nY << 0xf) >> 0x10;
    }

    p[0] = (u16)(pCell[1] & 0x7ff);
    p[1] = (u16)((pCell[1] >> 0xb) & 0x7ff);
    *(u32 *)(p + 4) = (pCell[0] + nOrigin) | 0x20000000;
    *(u32 *)(p + 6) = (nX + nY) & 0xffff;
    p[2] = (u16)((short *)p)[0];
    p[3] = (u16)((short *)p)[1];
    *(u32 *)((u8 *)p + 0x20) = 0;
    *((u8 *)p + 0x25) = 0;
    *(u32 *)((u8 *)p + 0x18) = 0x1000;
    *(u32 *)((u8 *)p + 0x1c) = 0x1000;
    p[0x14] = 0;
    p[0x13] = p[0x14];
    *(u8 *)(p + 0x15) = (u8)((*(u8 *)(p + 0x15) & ~0x1f) | 0x1f);

    if (bFree != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(p + 0x16));
    }
    *(u32 *)(p + 0x16) = 0;
    *(u32 *)((u8 *)p + 0x10) = 0x14000;
    *(u32 *)((u8 *)p + 0x14) = 0x14000;
}
