/* MobiClip: lay the movie out as a grid of bitmap sprites on one screen.
 *
 * Builds a whole OAM image in scratch memory: every entry parked off screen
 * first, then twelve 64x64 bitmap objects covering the 256x192 display in four
 * columns and three rows, sixteen scanlines down. The image is flushed and
 * handed to the requested engine, and the scratch buffer is given straight
 * back.
 */
typedef unsigned short u16;
typedef unsigned int u32;

#define OAM_BYTES        0x400
#define OAM_ENTRIES      0x80
#define OBJ_PARKED       0xc0
#define OBJ_BITMAP_64X64 0xc0000c00
#define OBJ_PRIORITY_PAL 0xfc00

#define REG_DISPCNT     (*(volatile u32 *)0x04000000)
#define REG_DB_DISPCNT  (*(volatile u32 *)0x04001000)
#define DISPCNT_OBJ     0x00400060
#define DISPCNT_OBJ_1D  0x00000020

typedef struct ObjEntry {
    u32 nAttr01;
    union {
        u32 nAttr23;
        struct {
            u16 nAttr2;
            u16 nAttr3;
        } h;
    } u;
} ObjEntry;

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 nSize, int nAlignment);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void DC_FlushRange(const void *pBlock, u32 nSize);
extern void GX_LoadOAM(const void *pSource, u32 nOffset, u32 nSize);
extern void GXS_LoadOAM(const void *pSource, u32 nOffset, u32 nSize);

void func_ov024_02083d0c(int bMainScreen)
{
    int nSprite = 0;
    ObjEntry *pOam;
    int i;
    int nX;
    int nY;
    int nRowTile;
    int nColTile;

    pOam = (ObjEntry *)NNS_FndAllocFromDefaultExpHeapEx(OAM_BYTES, 0x20);
    if (bMainScreen != 0) {
        REG_DISPCNT = (REG_DISPCNT & ~DISPCNT_OBJ) | DISPCNT_OBJ_1D;
    } else {
        REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x60) | DISPCNT_OBJ_1D;
    }

    for (i = 0; i < OAM_ENTRIES; i++) {
        pOam[i].nAttr01 = OBJ_PARKED;
        pOam[i].u.nAttr23 = 0;
    }

    for (nY = 0, nRowTile = 0; nY < 0xc0; nY += 0x40, nRowTile += 8) {
        for (nX = 0, nColTile = 0; nX < 0x100; nX += 0x40, nColTile += 8, nSprite++) {
            pOam[nSprite].nAttr01 = OBJ_BITMAP_64X64 | ((nY + 0x10) & 0xff)
                                | ((nX & 0x1ff) << 16);
            pOam[nSprite].u.h.nAttr2 =
                (u16)((nColTile + nRowTile * 32u) | OBJ_PRIORITY_PAL);
        }
    }

    DC_FlushRange(pOam, OAM_BYTES);
    if (bMainScreen != 0) {
        GX_LoadOAM(pOam, 0, OAM_BYTES);
    } else {
        GXS_LoadOAM(pOam, 0, OAM_BYTES);
    }
    NNSi_FndFreeFromDefaultHeap(pOam);
}
