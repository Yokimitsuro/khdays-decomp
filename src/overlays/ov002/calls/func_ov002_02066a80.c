/*
 * Builds the map panel page and hands back its first state.
 *
 * The page's own block is taken from the heap, published to the overlay's slot
 * and cleared, then the two sound tables are opened: twenty-two handles for the
 * grid cells and eight for the button row, with a pointer to each table left at
 * the end of the block so the cell lookup below can pick between them by group.
 *
 * The local player's current selection decides which handle is played on entry.
 * Cells zero and one sit in the first table unshifted, the grid cells from two
 * to twenty-three are shifted down by two, and the button row from twenty-four
 * up is shifted down by twenty-four, which is the same three-way split the
 * touch mapper produces.
 *
 * One thing here is load-bearing rather than style. The three-way split is
 * written as a plain cascade of less-than-or-equal tests, cheapest case first.
 * Written as a greater-than test with the two shifted cases nested inside, the
 * compiler lays the three arms out in the opposite order.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002MapPage {
    int nLocalPlayer;
    int bActive;
    char pad008[0xc];
    int aCellSounds[22];
    int aButtonSounds[8];
    int *apSoundTables[2];
} Ov002MapPage;

typedef struct Ov002MapSelection {
    int nGroup;
    int nField4;
    int nCell;
} Ov002MapSelection;

extern Ov002MapPage *data_ov002_0207f9f0;
extern const int data_ov002_0207e4a0[];
extern const int data_ov002_0207e480[];
extern int data_ov002_0207ee98;

extern Ov002MapPage *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *pDest, u8 nValue, u32 nSize);
extern void func_ov002_020538a0(int nMode);
extern void func_ov002_02053b28(int a, int b, int c, int d, int e);
extern int func_ov002_02053558(u16 nId);
extern void func_ov002_020535a4(int hSound);
extern int func_ov002_020536bc(int nKind);
extern void func_ov002_020536dc(int hItem, int nFlag);
extern void func_ov002_02052a6c(int *pTarget, void *pFn, int nArg);
extern int func_02030788(void);
extern Ov002MapSelection *func_ov002_02066248(int nPlayer);
extern void func_ov002_020669f8(int nGroup, int nFlag);
extern void func_ov002_02066920(int nCell, int hSound);
extern void func_ov002_02066970(int nValue, int nFlag);
extern int OS_IsThreadAvailable_0x0206373c(void);
extern int func_ov002_02053bb8(int nId);
extern void func_ov002_020667a0(int hCanvas, int hAnim, int a, int b, int c);
extern void func_ov002_02053cd4(int nId);
extern void func_ov002_0206625c(void);
extern void func_ov002_02066850(void);
extern void func_ov002_02066bd8(void);

void *func_ov002_02066a80(void)
{
    Ov002MapPage *pPage;
    Ov002MapSelection *pSel;
    int i;
    int nCell;
    int nIndex;
    int hCanvas;
    int hAnim;

    pPage = NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f9f0 = pPage;
    MI_CpuFill8(pPage, 0, 0x94);
    pPage->bActive = 1;
    func_ov002_020538a0(1);

    func_ov002_02053b28(0x1a, 0, 0, 0x20, 0x18);
    func_ov002_020535a4(func_ov002_02053558(0x3e6));
    func_ov002_020536dc(func_ov002_020536bc(6), 1);
    func_ov002_02052a6c(&data_ov002_0207ee98, func_ov002_02066850, 0);

    for (i = 0; i < 22; i++) {
        pPage->aCellSounds[i] = func_ov002_02053558((u16)data_ov002_0207e4a0[i]);
    }
    for (i = 0; i < 8; i++) {
        pPage->aButtonSounds[i] = func_ov002_02053558((u16)data_ov002_0207e480[i]);
    }

    pPage->apSoundTables[0] = pPage->aCellSounds;
    pPage->apSoundTables[1] = pPage->aButtonSounds;

    pPage->nLocalPlayer = func_02030788();
    pSel = func_ov002_02066248(func_02030788());
    func_ov002_020669f8(pSel->nGroup, 1);

    nCell = pSel->nCell;
    if (nCell <= 1) {
        nIndex = nCell;
    } else if (nCell <= 0x17) {
        nIndex = nCell - 2;
    } else {
        nIndex = nCell - 0x18;
    }
    func_ov002_02066920(nCell, pPage->apSoundTables[pSel->nGroup][nIndex]);
    func_ov002_02066970(pSel->nField4, 1);

    hCanvas = OS_IsThreadAvailable_0x0206373c();
    hAnim = func_ov002_02053bb8(0x1a);
    func_ov002_020667a0(hCanvas, hAnim, 3, 4, 0xd);
    func_ov002_02053cd4(0x1a);
    func_ov002_0206625c();
    return func_ov002_02066bd8;
}
