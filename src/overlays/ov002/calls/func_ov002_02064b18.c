/*
 * Ov002_ShowPageSpread - put the whole page spread on screen.
 *
 * With nothing loaded the object is just released. Otherwise the three parts of
 * the object are opened - the palette, the character data and the tile map -
 * the map is uploaded, and the other two are handed to the graphics queue.
 *
 * The row of seven marks that goes underneath is built last: a mark is lit
 * where the flag word has its bit and blank where it does not.
 *
 * THUMB.
 */

typedef unsigned short u16;

typedef struct {
    char pad000[0xc];
    int nPalette;
} Ov002PagePart;

typedef struct {
    char pad000[0x10];
    int nCharBase;
    int nCharSize;
} Ov002PageChars;

extern int data_ov002_0207f638;

extern void *NNS_FndAllocFromDefaultExpHeapEx(int nSize, int nAlign);
extern void GFXi_EnqueueCommand(int nCmd, int nDest, int nSrc, int nSize);
extern void func_02011988(int hPart, void *pOut);
extern void func_02011a20(int hPart, void *pOut);
extern void func_02011a6c(int hPart, void *pOut);
extern void func_02025464(int hObj, int nMode);
extern int func_020255d4(int hObj, int nPart, int nFlags);

extern int func_ov002_02052aec(int pObj);
extern void func_ov002_02052af4(int pObj, int nMode);
extern void func_ov002_02053d28(int a, int b, int c, int d, int e);
extern int func_ov002_02063610(void);
extern void func_ov002_0206484c(u16 *pMap);

void func_ov002_02064b18(int pObj)
{
    Ov002PagePart *pPal;
    Ov002PageChars *pChars;
    u16 *pMap;
    int hObj;
    int nMask;
    u16 *pBuf;
    int i;
    int nEntry;

    if (data_ov002_0207f638 == 0) {
        func_ov002_02052af4(pObj, 1);
        return;
    }

    hObj = func_ov002_02052aec(pObj);
    func_02025464(hObj, 1);
    func_02011a20(func_020255d4(hObj, 0, 0), &pPal);
    func_02011988(func_020255d4(hObj, 1, 0), &pChars);
    func_02011a6c(func_020255d4(hObj, 6, 0), &pMap);

    func_ov002_0206484c(pMap);
    GFXi_EnqueueCommand(0x1f, 0, pPal->nPalette, 0x140);
    func_ov002_02053d28(0x16, 0x1f20, pChars->nCharSize, pChars->nCharBase,
                        hObj);
    func_ov002_02052af4(pObj, 0);

    nMask = func_ov002_02063610();
    pBuf = (u16 *)NNS_FndAllocFromDefaultExpHeapEx(0x10, 4);
    pBuf[0] = 0;
    for (i = 0; i < 7; i++) {
        if ((nMask & (1 << i)) != 0) {
            nEntry = 0x1d;
        } else {
            nEntry = 0x14a5;
        }
        pBuf[i + 1] = (u16)nEntry;
    }
    func_ov002_02053d28(0x1f, 0x160, (int)pBuf, 0x10, 0);
}
