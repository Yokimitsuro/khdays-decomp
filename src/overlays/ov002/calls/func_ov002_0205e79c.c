/*
 * Ov002_SceneApplyPanelRequest - take a filled-in panel request and set the
 * scene up for it: the four strings, the optional picture, and the window.
 *
 * The two words the request carries for the caption box are copied straight
 * across, then the four strings are handed to the owner that replaces them. Any
 * picture the scene was already holding is freed. A request with a negative
 * picture index leaves the scene without one; otherwise the file is loaded out
 * of the archive - its id is the packed sector of the scene's own archive base
 * plus the file number from the table - and its sprite set is bound. The label
 * that goes with the picture is drawn twice, once per shadow, into a scratch
 * copy of the picture's tiles that is swapped in and out around the drawing; a
 * label wider than 0x3c pixels borrows a second font for the duration.
 *
 * The window is measured last, and the entry count decides whether the lower
 * box is filled in at all.
 *
 * THUMB.
 *
 * The record pointer and the two scratch arrays share one block, and the pointer
 * is volatile. Both halves are load-bearing and neither works alone.
 *
 * The block fixes the frame: the arrays are what the calls take the address of,
 * so grouping the pointer with them puts it at the offset the original uses and
 * leaves the font handle the one word below it. As two plain locals the two are
 * spilled as ordinary temporaries and the compiler hands out their slots in spill
 * order, which comes out the other way round; no declaration order fixes that,
 * because their slots are not decided by declaration rank at all.
 *
 * The volatile is what makes the pointer reload. The original stores the call
 * result to its slot and reads it back three instructions later for the argument;
 * without the qualifier the compiler keeps a copy in a register instead, which
 * costs one copy and saves one reload - the same instruction count, the wrong
 * instructions. The same device is recorded on the matched twin
 * func_ov002_0205d478, which steps the panel cursor for this same screen.
 */

typedef unsigned short u16;

extern int data_ov002_0207f624;
extern u16 data_ov002_0207deb8[];
extern u16 data_ov002_0207deba[];
extern int data_ov002_0207eb58[];

extern void NNSi_FndFreeFromDefaultHeap(int pBlock);
extern int func_0201ef9c(unsigned int nFileId, int nHeap);
extern void func_02024c94(int *pSet, int pFile, int a, int b, int c);
extern void MIi_CpuCopyFast(const void *pSrc, void *pDst, unsigned int nSize);
extern void func_0202ff58(int *pBind, const int *pTable);
extern void func_0202ff7c(int *pBind);
extern int func_02013768(int nFont, int nOpts, int nText, int *pOut);
extern void func_020301c8(void *pSurface, int nX, int nY, int nPalette,
                          int nFlags, int nText);

extern void func_ov002_0205e5bc(int *pSlot, short *pText);
extern int func_ov002_0205740c(void);
extern int *func_ov002_02052844(int *pSet, unsigned int nIndex);
extern int func_ov002_0205e674(int *pLayout, int *pReq);

typedef struct {
    int *volatile pText;
    int aBind[3];
    int aLayout[12];
} Ov002ApplyFrame;

void func_ov002_0205e79c(int *pReq)
{
    Ov002ApplyFrame f;
    int *ctx;
    int *pWindow;
    int nHandle;
    int nWidth;
    int nCount;
    int bWide;

    ctx = *(int **)&data_ov002_0207f624;
    pWindow = (int *)((char *)ctx + 0x668);
    *(int *)((char *)ctx + 0x69c) = pReq[7];
    *(int *)((char *)ctx + 0x6a0) = pReq[8];

    func_ov002_0205e5bc((int *)((char *)ctx + 0x7c0), (short *)pReq[0]);
    func_ov002_0205e5bc((int *)((char *)ctx + 0x7c4), (short *)pReq[1]);
    func_ov002_0205e5bc((int *)((char *)ctx + 0x7c8), (short *)pReq[2]);
    func_ov002_0205e5bc((int *)((char *)ctx + 0x7cc), (short *)pReq[3]);

    if (*(int *)((char *)ctx + 0x68c) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)((char *)ctx + 0x68c));
        *(int *)((char *)ctx + 0x68c) = 0;
    }

    if (pReq[5] >= 0) {
        *(int *)((char *)ctx + 0x68c) = func_0201ef9c(
            ((*(int *)((char *)ctx + 0x7e4) + 0x8000) & 0xfffffc) << 7
                | 0x80000000
                | (data_ov002_0207deb8[pReq[5] * 2] & 0x1ff),
            0xe);
        func_02024c94(pWindow + 10, *(int *)((char *)ctx + 0x68c), 0, 0, 0);
        MIi_CpuCopyFast(*(int **)(pWindow[0xb] + 0x14),
                        *(int **)(*(int *)((char *)ctx + 0x788) + 0x20), 0x3840);

        func_0202ff58(f.aBind, data_ov002_0207eb58);
        nHandle = func_ov002_0205740c();
        f.pText = func_ov002_02052844((int *)((char *)ctx + 0x7ac),
                                    data_ov002_0207deba[pReq[5] * 2]);
        nWidth = func_02013768(*(int *)((char *)ctx + 0x790),
                               *(int *)((char *)ctx + 0x794), (int)f.pText, 0);
        if (nWidth > 0x3c) {
            bWide = 1;
        } else {
            bWide = 0;
        }
        if (bWide) {
            *(int **)((char *)ctx + 0x790) = f.aBind;
        }
        func_020301c8((char *)ctx + 0x770, 0x58, 0x6c, 0xf1, 0x411, (int)f.pText);
        func_020301c8((char *)ctx + 0x770, 0x57, 0x6b, 0xf2, 0x411, (int)f.pText);
        if (bWide) {
            *(int *)((char *)ctx + 0x790) = nHandle;
        }
        func_0202ff7c(f.aBind);
        MIi_CpuCopyFast(*(int **)(*(int *)((char *)ctx + 0x788) + 0x20),
                        *(int **)(pWindow[0xb] + 0x14), 0x3840);
    } else {
        *(int *)((char *)ctx + 0x68c) = 0;
    }

    nCount = func_ov002_0205e674(f.aLayout, pReq);
    pWindow[0] = f.aLayout[0];
    pWindow[1] = f.aLayout[1];
    pWindow[2] = f.aLayout[2];
    pWindow[3] = f.aLayout[3];
    pWindow[5] = pReq[4];
    *(int *)((char *)ctx + 0x6a8) = f.aLayout[5];
    *(int *)((char *)ctx + 0x6ac) = f.aLayout[4];
    *(int *)((char *)ctx + 0x6b0) = f.aLayout[6];
    *(int *)((char *)ctx + 0x6b4) = f.aLayout[7];
    *(int *)((char *)ctx + 0x6b8) = 0xe1;
    *(int *)((char *)ctx + 0x6bc) = 0xf;
    *(int *)((char *)ctx + 0x6c4) = 5;
    *(int *)((char *)ctx + 0x6cc) = 0x40;

    if (nCount > 0) {
        *(int *)((char *)ctx + 0x7e0) = nCount;
        *(int *)((char *)ctx + 0x7dc) = pReq[6];
        *(int *)((char *)ctx + 0x6d0) = f.aLayout[9];
        *(int *)((char *)ctx + 0x6d4) = f.aLayout[8];
        *(int *)((char *)ctx + 0x6d8) = f.aLayout[10];
        *(int *)((char *)ctx + 0x6dc) = f.aLayout[11];
        *(int *)((char *)ctx + 0x6e0) = *(int *)((char *)ctx + 0x6b0)
                                        * *(int *)((char *)ctx + 0x6b4) + 0xe1;
        *(int *)((char *)ctx + 0x6e4) = 0xf;
        *(int *)((char *)ctx + 0x6ec) = 5;
        *(int *)((char *)ctx + 0x6f4) = 0x40;
    } else {
        *(int *)((char *)ctx + 0x7e0) = 0;
        *(int *)((char *)ctx + 0x7dc) = 0;
    }
}
